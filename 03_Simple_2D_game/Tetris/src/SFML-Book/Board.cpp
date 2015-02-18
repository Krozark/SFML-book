#include <SFML-Book/Board.hpp>

#include <cstring> // momory management like memset
#include <cassert> //< for debug

#define CELL_EMPTY -1

namespace book
{
Board::Board(int columns,int lines,int cell_x,int cell_y):
    _columns(columns),
    _lines(lines),
    _cellX(cell_x),
    _cellY(cell_y),
    _isGameOver(false),
    _gridContent(nullptr)
{
    //build the grid content and set it to empty(0)
    _gridContent = new int[_lines*_columns];
    std::memset(_gridContent,CELL_EMPTY,_lines*_columns*sizeof(int));

    //make the grid color
    sf::Color grid_color(55,55,55);
    //build the shape borders
    _grid = sf::VertexArray(sf::Lines,(_lines+1+_columns+1)*2);
    for(int i=0;i<=_lines;++i)
    {
        _grid[i*2] = sf::Vertex(sf::Vector2f(0,i*_cellY));
        _grid[i*2+1] = sf::Vertex(sf::Vector2f(_columns*_cellX,i*_cellY));

        _grid[i*2].color = grid_color;
        _grid[i*2+1].color = grid_color;
    }
    for(int i=0;i<=columns;++i)
    {
        _grid[(_lines+1)*2 + i*2] = sf::Vertex(sf::Vector2f(i*_cellX,0));
        _grid[(_lines+1)*2 + i*2+1] = sf::Vertex(sf::Vector2f(i*_cellX,_lines*_cellY));

        _grid[(_lines+1)*2 + i*2].color = grid_color;
        _grid[(_lines+1)*2 + i*2+1].color = grid_color;
    }
}

Board::~Board()
{
    delete _gridContent;
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //make states
    states.transform *= getTransform();

    //draw each square of pieces
    for(int y=0; y<_lines; ++y)
        for(int x=0; x<_columns; ++x)
        {
            if(_gridContent[y*_columns + x] != CELL_EMPTY)
            {
                sf::RectangleShape rectangle(sf::Vector2f(_cellX,_cellY));
                rectangle.setFillColor(Piece::Tetrimino_colors[_gridContent[y*_columns + x]]);
                rectangle.setPosition(x*_cellX,y*_cellY);
                target.draw(rectangle,states);
            }
        }
    
    //draw the grid
    target.draw(_grid,states);
}

void Board::spawn(Piece& piece)
{
    //set piece spawn origin
    piece.setPosition(_columns/2,0);
    //add it in the grid
    clear(piece);
    for(int x=0;x<_columns;++x)
        if(_gridContent[x] != CELL_EMPTY)
        {
            _isGameOver = true;
            break;
        }
    draw(piece);
}

bool Board::move(Piece& piece, int delta_x,int delta_y)
{
    delta_x += piece.getPosX();
    delta_y += piece.getPosY();

    //delete the piece to not collide with itself
    clear(piece);

    //flood test
    bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = {{false}};
    bool movable = true;

    flood(delta_x,
          delta_y,
          (int)Piece::PIVOT_X,
          (int)Piece::PIVOT_Y,
          piece.getType(),
          piece.getRotation(),
          visited,
          movable);

    //add it to the grid
    if(movable)
        piece.setPosition(delta_x,delta_y);
    draw(piece);

    return movable;
}
bool Board::isFallen(const Piece& piece)
{
    //delete the piece to not test collision with itself
    clear(piece);

    //flood test
    bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = {{false}};
    bool fallen = true;

    flood(piece.getPosX(),
          piece.getPosY()+1,
          (int)Piece::PIVOT_X,
          (int)Piece::PIVOT_Y,
          piece.getType(),
          piece.getRotation(),
          visited,
          fallen);

    //add it to the grid
    draw(piece);

    return fallen;
}

void Board::drop(Piece& piece)
{
    //move down the piece as we can
    while(move(piece,0,1));
}

bool Board::rotateLeft(Piece& piece)
{
    int rotation = piece.getRotation();
    if(rotation > 0)
        --rotation;
    else
        rotation = Piece::NB_ROTATIONS - 1;
    return rotate(piece,rotation);
    
}

bool Board::rotateRight(Piece& piece)
{
    int rotation = piece.getRotation();
    if(rotation < Piece::NB_ROTATIONS -1)
        ++rotation;
    else
        rotation = 0;

    return rotate(piece,rotation);
}

bool Board::isGameOver()
{
    return _isGameOver;
}

bool Board::rotate(Piece& piece,int rotation)
{
    //debug test
    assert(rotation >= 0 and rotation < Piece::NB_ROTATIONS);

    //delete the piece of the grid
    clear(piece);

    //flood call
    bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = {{false}};
    bool rotable = true;

    flood((int)piece.getPosX(),
          (int)piece.getPosY(),
          (int)Piece::PIVOT_X,
          (int)Piece::PIVOT_Y,
          piece.getType(),
          rotation,
          visited,
          rotable);

    //add it to the grid
    if(rotable)
        piece.setRotation(rotation);
    draw(piece);

    return rotable;
}


void Board::draw(const Piece& piece)
{
    //call of flood with the value as the piece type
    flood(piece,piece.getType());
}

void Board::clear(const Piece& piece)
{
    //call of flood with empty value
    flood(piece,CELL_EMPTY);
}


void Board::flood(const Piece& piece,int value)
{
    bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = {{false}};

    flood((int)piece.getPosX(),
          (int)piece.getPosY(),
          (int)Piece::PIVOT_X,
          (int)Piece::PIVOT_Y,
          piece.getType(),
          piece.getRotation(),
          visited,
          value);
}

void Board::flood(int grid_x,int grid_y,int piece_x,int piece_y,Piece::Tetrimino_Types type,int rotation,bool visited[][Piece::MATRIX_SIZE],int value)
{
    //limit tests
    if(piece_x < 0 or piece_x >= Piece::MATRIX_SIZE
       or piece_y < 0 or piece_y >= Piece::MATRIX_SIZE 
       or grid_x < 0 or grid_x >= (int)_columns
       or grid_y < 0 or grid_y >= (int)_lines
       or visited[piece_y][piece_x] == true
       or Piece::Tetrimino_Pieces[type][rotation][piece_y][piece_x] == 0)
        return;

    //set the visited boolean
    visited[piece_y][piece_x] = true;

    //add the value to the grid
    _gridContent[grid_y*_columns + grid_x] = value;

    //recursiv call for each square around : 4 directions
    flood(grid_x, grid_y-1, piece_x, piece_y-1, type, rotation, visited, value);
    flood(grid_x+1, grid_y, piece_x+1, piece_y, type, rotation, visited, value);
    flood(grid_x, grid_y+1, piece_x, piece_y+1, type, rotation, visited, value);
    flood(grid_x-1, grid_y, piece_x-1, piece_y, type, rotation, visited, value);
}

void Board::flood(int grid_x,int grid_y,int piece_x,int piece_y,Piece::Tetrimino_Types type,int rotation,bool visited[][Piece::MATRIX_SIZE],bool& flag)
{
    //limit tests
    if(piece_x < 0 or piece_x >= Piece::MATRIX_SIZE
       or piece_y < 0 or piece_y >= Piece::MATRIX_SIZE 
       or visited[piece_y][piece_x] == true
       or Piece::Tetrimino_Pieces[type][rotation][piece_y][piece_x] == 0)
        return;

    //set the visited boolean
    visited[piece_y][piece_x] = true;

    //collision tests
    if(grid_x < 0 or grid_x >= (int)_columns
       or grid_y < 0 or grid_y >= (int)_lines
       or _gridContent[grid_y*_columns + grid_x] != CELL_EMPTY)
    {
        flag = false;
        return;
    }

    //recursiv call for each square around : 4 directions
    flood(grid_x, grid_y-1, piece_x, piece_y-1, type, rotation, visited, flag);
    flood(grid_x+1, grid_y, piece_x+1, piece_y, type, rotation, visited, flag);
    flood(grid_x, grid_y+1, piece_x, piece_y+1, type, rotation, visited, flag);
    flood(grid_x-1, grid_y, piece_x-1, piece_y, type, rotation, visited, flag);
}


void Board::clearLine(int yy)
{
   assert(yy < _lines);

    for(int y=yy; y>0; --y)
        for(int x=0; x<_columns; ++x)
            _gridContent[y*_columns + x] = _gridContent[(y-1)*_columns + x];

}

int Board::clearLines(const Piece& piece)
{
    int nb_delete = 0;
    
    clear(piece);

    //for each line
    for(int y=0; y<_lines; ++y)
    {
        //for each cell
        int x =0;
        for(;_gridContent[y*_columns + x] != CELL_EMPTY and x<_columns; ++x);
        //if the line is complete
        if(x == _columns)
        {
            //delete it
            clearLine(y);
            ++nb_delete;
        }
    }
    draw(piece);
    
    return nb_delete;
}
}
