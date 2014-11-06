#include <SFML-Book/Stats.hpp>

#define FONT_SIZE   24

namespace book
{

Stats::Stats() : _nb_rows(0), _nb_score(0), _nb_lvl(0), _is_game_over(false)
{
    _font.loadFromFile("media/fonts/trs-million.ttf");

    _text_rows.setFont(_font);
    _text_rows.setString("rows : 0");
    _text_rows.setCharacterSize(FONT_SIZE);
    _text_rows.setPosition(0,0);

    _text_score.setFont(_font);
    _text_score.setString("score : 0");
    _text_score.setCharacterSize(FONT_SIZE);
    _text_score.setPosition(0,FONT_SIZE + 1);

    _text_lvl.setFont(_font);
    _text_lvl.setString("lvl : 0");
    _text_lvl.setCharacterSize(FONT_SIZE);
    _text_lvl.setPosition(0,(FONT_SIZE + 1)*2);

    _text_game_over.setFont(_font);
    _text_game_over.setString("Game Over");
    _text_game_over.setCharacterSize(72);
    _text_game_over.setPosition(0,0);
}

void Stats::gameOver()
{
    _is_game_over = true;
}

void Stats::addLines(int lines)
{
    if(lines > 0)
    {
        //update number of lines
        _nb_rows += lines;
        _text_rows.setString("rows : "+std::to_string(_nb_rows));

        //update the score
        _text_score.setString("score : "+std::to_string(_nb_score));
        
        switch (lines)
        {
            case 1 : _nb_score += 40 * (_nb_lvl+1);break;
            case 2 : _nb_score += 100 * (_nb_lvl+1);break;
            case 3 : _nb_score += 300 * (_nb_lvl+1);break;
            case 4 : _nb_score += 1200 * (_nb_lvl+1);break;
            default :break;
        }

        _nb_lvl = _nb_rows / 10;

        //update the lvl
        _text_lvl.setString("lvl : "+std::to_string(_nb_lvl));
    }
}

unsigned int Stats::getLvl()const
{
    return _nb_lvl;
}

void Stats::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(not _is_game_over)
    {
        //make states
        states.transform *= getTransform();
        
        //draw
        target.draw(_text_rows,states);
        target.draw(_text_score,states);
        target.draw(_text_lvl,states);
    }
    else
        target.draw(_text_game_over,states);
}

}
