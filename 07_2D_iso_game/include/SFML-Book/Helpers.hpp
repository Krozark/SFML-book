#ifndef BOOK_HELPERS_HPP
#define BOOK_HELPERS_HPP

#include <SFML-utils/ES.hpp>
#include <SFML-utils/Map.hpp>

#include <SFML-Book/Entity.hpp>

namespace book
{
    class Team;

    std::uint32_t makeMain(sfutils::EntityManager<Entity>& manager,sfutils::Layer<sfutils::HexaIso,Entity*>& layer,Team* team);

}
#endif
