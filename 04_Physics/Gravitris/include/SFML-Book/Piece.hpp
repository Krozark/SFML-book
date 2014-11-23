#ifndef BOOK_PIECE_HPP
#define BOOK_PIECE_HPP

#include <SFML/Graphics.hpp> //Drawable
#include <Box2D/Box2D.h>

namespace book
{
    class Piece : public sf::Drawable
    {
        public:
            Piece(const Piece&) = delete;
            Piece& operator=(const Piece&) = delete;

            enum Tetrimino_Types {O=0,I,S,Z,L,J,T,SIZE}; //< different kind of pieces            
            static const sf::Color Tetrimino_colors[Tetrimino_Types::SIZE]; //< different colors for each kind of piece
            

            Piece(b2World& world,int pos_x,int pos_y,Tetrimino_Types type,float rotation); //< constructor
            ~Piece();

            void update();

        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            b2Fixture* create_part(int pos_x,int pos_y,float rotation,Tetrimino_Types type); ///< position is relaive to the piece int the matric coordonate (0 to 3)

            b2Body * _body;
            b2World& _world;
    };
}
#endif
