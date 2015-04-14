#include <SFML-Book/Stats.hpp>
#include <SFML-Book/Configuration.hpp>

#define FONtSIZE   24

namespace book
{

    Stats::Stats() : _nbRows(0), _nbScore(0), _nbLvl(0), _isGameOver(false)
    {
        _textRows.setFont(Configuration::fonts.get(Configuration::Fonts::Gui));
        _textRows.setString("rows : 0");
        _textRows.setCharacterSize(FONtSIZE);
        _textRows.setPosition(0,0);

        _textScore.setFont(Configuration::fonts.get(Configuration::Gui));
        _textScore.setString("score : 0");
        _textScore.setCharacterSize(FONtSIZE);
        _textScore.setPosition(0,FONtSIZE + 1);

        _textLvl.setFont(Configuration::fonts.get(Configuration::Gui));
        _textLvl.setString("lvl : 0");
        _textLvl.setCharacterSize(FONtSIZE);
        _textLvl.setPosition(0,(FONtSIZE + 1)*2);

        _textGameOver.setFont(Configuration::fonts.get(Configuration::Gui));
        _textGameOver.setString("Game Over");
        _textGameOver.setCharacterSize(72);
        _textGameOver.setPosition(0,0);
    }

    bool Stats::isGameOver()const
    {
        return _isGameOver;
    }

    void Stats::setGameOver(bool g)
    {
        _isGameOver = g;
    }

    int Stats::getLevel()const
    {
        return _nbLvl;
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
                default : _nbScore += 1200 * (_nbLvl+1);break;
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
        }
        else
            target.draw(_textGameOver,states);
    }

}
