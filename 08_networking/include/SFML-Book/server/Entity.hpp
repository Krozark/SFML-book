#ifndef BOOK_ENTITY_HPP
#define BOOK_ENTITY_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Core.hpp>

namespace book
{
    class Game;
    class Entity : public sfutils::Entity<Entity>
    {

        public:
            Entity(const Entity&) = delete;
            Entity& operator=(const Entity&) = delete;

            Entity(sfutils::EntityManager<Entity>* manager,std::uint32_t id);

            sf::Vector2f getPosition()const;
            sf::Vector2i getCoord()const;

            void setType(short int type);
            short int getType()const;

            using FuncType = std::function<void(Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Game& game)>;


            FuncType onHit;
            FuncType onHitted;

        private:
            friend class Game;

            void setPosition(const sf::Vector2f& pos,const sf::Vector2i& coord);

            sf::Vector2f _position;
            sf::Vector2i _coords;
            short int _type;
    };

}
#endif
