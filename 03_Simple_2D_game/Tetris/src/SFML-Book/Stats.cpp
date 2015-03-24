#include <SFML-Book/Stats.hpp>

#define FONT_SIZE   24

namespace book
{

Stats::Stats() : _nbRows(0), _nbScore(0), _nbLvl(0), _isGameOver(false)
{
    _font.loadFromFile("media/fonts/trs-million.ttf");

    _textRows.setFont(_font);
    _textRows.setString("rows : 0");
    _textRows.setCharacterSize(FONT_SIZE);
    _textRows.setPosition(0,0);

    _textScore.setFont(_font);
    _textScore.setString("score : 0");
    _textScore.setCharacterSize(FONT_SIZE);
    _textScore.setPosition(0,FONT_SIZE + 1);

    _textLvl.setFont(_font);
    _textLvl.setString("lvl : 0");
    _textLvl.setCharacterSize(FONT_SIZE);
    _textLvl.setPosition(0,(FONT_SIZE + 1)*2);

    _textInformation.setFont(_font);
    _textInformation.setString("Use arrow keys to move\n\tS and D to rotate");
    _textInformation.setColor(sf::Color(0,255,0));
    _textInformation.setCharacterSize(FONT_SIZE);
    _textInformation.setPosition(0,(FONT_SIZE + 1)*4);

    _textGameOver.setFont(_font);
    _textGameOver.setString("Game Over");
    _textGameOver.setCharacterSize(72);
    _textGameOver.setPosition(0,0);
}

void Stats::gameOver()
{
    _isGameOver = true;
}

void Stats::addLines(int lines)
{
    if(lines > 0)
    {
        //update number of lines
        _nbRows += lines;
        _textRows.setString("rows : "+std::to_string(_nbRows));

        //update the score
        _textScore.setString("score : "+std::to_string(_nbScore));

        switch (lines)
        {
            case 1 : _nbScore += 40 * (_nbLvl+1);break;
            case 2 : _nbScore += 100 * (_nbLvl+1);break;
            case 3 : _nbScore += 300 * (_nbLvl+1);break;
            case 4 : _nbScore += 1200 * (_nbLvl+1);break;
            default :break;
        }

        _nbLvl = _nbRows / 10;

        //update the lvl
        _textLvl.setString("lvl : "+std::to_string(_nbLvl));
    }
}

unsigned int Stats::getLvl()const
{
    return _nbLvl;
}

void Stats::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(not _isGameOver)
    {
        //make states
        states.transform *= getTransform();

        //draw
        target.draw(_textRows,states);
        target.draw(_textScore,states);
        target.draw(_textLvl,states);
        target.draw(_textInformation,states);
    }
    else
        target.draw(_textGameOver,states);
}

}
