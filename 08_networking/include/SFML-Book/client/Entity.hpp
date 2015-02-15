#ifndef BOOK_ENTITY_HPP
#define BOOK_ENTITY_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Map.hpp>
#include <SFML-utils/Core.hpp>

#include <SFML-Book/common/Packet.hpp>

namespace book
{
    class Level;
    class Team;

    class Entity : public sfutils::Entity<Entity>, public sf::Drawable
    {
        public:
            Entity(const Entity&) = delete;
            Entity& operator=(const Entity&) = delete;

            Entity(sfutils::EntityManager<Entity>* manager,std::uint32_t id);

            sf::Vector2f getPosition()const;
            void setPosition(const sf::Vector2f& pos);

            std::string name;

            using FuncType = std::function<void(Entity& self,const sf::Vector2i& myCoord,Entity& enemi,const sf::Vector2i& enemyCoord,Level& level)>;

            FuncType onHit;
            FuncType onHitted;

        private:
            virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
    };


    void makeAs(unsigned int entityType,Entity& e,Team* team,Level& level,const packet::CreateEntity::Data& data);

    void makeAsMain(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data);
    void makeAsEye(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data);
    void makeAsWormEgg(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data);
    void makeAsWorm(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data);
    void makeAsCarnivor(Entity& entity,Team* team,Level& level,const packet::CreateEntity::Data& data);


}
#endif
