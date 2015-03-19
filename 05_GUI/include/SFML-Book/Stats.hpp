#ifndef STATS_HPP
#define STATS_HPP

#include <SFML/Graphics.hpp>

namespace book
{
    class Stats : public sf::Transformable,public sf::Drawable
    {
        public:
            Stats();

            void addLines(int lines);
            unsigned int getLvl()const;

            bool isGameOver()const;
            void setGameOver(bool);

            int getLevel()const;
            void setLevel(int lvl);

            void reset();

        private:
            virtual void draw(sf::RenderTarget& target,sf::RenderStates states=sf::RenderStates::Default) const override; //< draw override from Drawable

            unsigned int _nbRows;
            unsigned int _nbScore;
            unsigned int _nbLvl;

            unsigned int _initialLvl;

            bool _isGameOver;

            sf::Text _textRows;
            sf::Text _textScore;
            sf::Text _textLvl;
            sf::Text _textGameOver;
    };
}
#endif
