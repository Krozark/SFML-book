#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>

namespace book
{
    class Board;

    class Piece
    {
        public:
            /** static members **/
            static const unsigned short int NB_ROTATIONS = 4; //< number of rotations
            static const unsigned short int MATRIX_SIZE = 4; //< size of the matrix

            static const unsigned int PIVOT_Y = 1; //< pivot Y coord in the Tetrimino_Pieces matrix
            static const unsigned int PIVOT_X = 2;//< pivot X coord ine the Tetrimino_Pieces matrix

            enum Tetrimino_Types {O=0,I,S,Z,L,J,T,SIZE}; //< different kind of pieces
            static const sf::Color Tetrimino_colors[Tetrimino_Types::SIZE]; //< different colors for each kind of piece
            static const char Tetrimino_Pieces[Tetrimino_Types::SIZE][NB_ROTATIONS][MATRIX_SIZE][MATRIX_SIZE];//< store all the different shapes

            /** Not capyable **/

            Piece(const Piece&) = delete;
            Piece& operator=(const Piece&) = delete;

            Piece(Tetrimino_Types type,short int rotation); //< constructor


            // type
            Tetrimino_Types getType()const;

            //rotation
            void setRotation(short int rotation); //< set the rotation
            short int getRotation()const;
            
            //position
            void setPosition(int x,int y);//< set the position in the board

            int getPosX()const;
            int getPosY()const;
            
            //clock
            sf::Time getTimeSinceLastMove()const;


        private:
            const Tetrimino_Types _type; //< the piece type
            short int _rotation; //< the piece rotaton

            int _positionX; //< position in the board
            int _positionY;//< position in the board
            
            sf::Clock _clockSinceLastMove;
    };
}
#endif
