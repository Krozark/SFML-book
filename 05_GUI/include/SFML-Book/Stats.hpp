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

            unsigned int _nb_rows;
            unsigned int _nb_score;
            unsigned int _nb_lvl;

            unsigned int _initial_lvl;

            bool _is_game_over;

            sf::Text _text_rows;
            sf::Text _text_score;
            sf::Text _text_lvl;
            sf::Text _text_game_over;
    };
}
#endif
