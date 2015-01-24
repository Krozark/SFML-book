#ifndef BOOK_ENTITY_HPP
#define BOOK_ENTITY_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Core.hpp>

namespace book
{
    class Entity : public sfutils::Entity<Entity>, public sf::Drawable
    {

        public:
            Entity(const Entity&) = delete;
            Entity& operator=(const Entity&) = delete;

            Entity(sfutils::EntityManager<Entity>* manager,std::uint32_t id);

            sf::Vector2f getPosition()const;
            void setPosition(const sf::Vector2f& pos);

        private:
            virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
    };

}
#endif
