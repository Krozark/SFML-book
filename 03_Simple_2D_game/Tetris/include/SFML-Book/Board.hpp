#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <SFML-Book/Piece.hpp>


namespace book
{
    /**
     * \brief Class to manage the game board.
     * Inherit from Drawable to desplay it on screen
     */
    class Board : public sf::Transformable,public sf::Drawable
    {
        public:
            //Make the class non copyable
            Board(const Board&) = delete;
            Board& operator=(const Board&) = delete;

            static const int DEFAULT_BOARD_COLUMNS = 10; //< default colums number
            static const int DEFAULT_BOARD_LINE = 20;//< default line number
            static const int DEFAULT_cellX = 24;
            static const int DEFAULT_cellY = 24;


            Board(int columns=DEFAULT_BOARD_COLUMNS,int line=DEFAULT_BOARD_LINE,int cell_x=DEFAULT_cellX,int cell_y=DEFAULT_cellY);

            ~Board();


            void spawn(Piece& piece);
            bool move(Piece& piece, int delta_x,int delta_y);
            bool isFallen(const Piece& piece);
            void drop(Piece& piece);
            bool rotateLeft(Piece& piece);
            bool rotateRight(Piece& piece);

            bool isGameOver();
            int clearLines(const Piece& piece); //< clear all possible lines

        private:
            bool rotate(Piece& piece,int rotation);

            void draw(const Piece& piece);
            void clear(const Piece& piece);

            virtual void draw(sf::RenderTarget& target,sf::RenderStates states=sf::RenderStates::Default) const override; //< draw override from Drawable


            void flood(const Piece& piece,int value);
            void flood(int grid_x,int grid_y,int piece_x,int piece_y,Piece::Tetrimino_Types type,int rotation,bool visited[][Piece::MATRIX_SIZE],int value);
            void flood(int grid_x,int grid_y,int piece_x,int piece_y,Piece::Tetrimino_Types type,int rotation,bool visited[][Piece::MATRIX_SIZE],bool& flag);

            void clearLine(int y); //< clear a line

            const int _columns;
            const int _lines;
            const int _cellX;
            const int _cellY;

            bool _isGameOver;

            sf::VertexArray _grid;//< grid borders
            int* _gridContent;//< lines * columns
    };
}
#endif
