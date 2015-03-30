#ifndef BOOK_TEAM_HPP
#define BOOK_TEAM_HPP

#include <vector>
#include <list>
#include <cstdint>

#include <SFML/Graphics.hpp>

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

namespace book
{
    class Client;
    class Game;
}

class Team : public orm::SqlObject<Team>
{
    public:
        Team(const Team&) = delete;
        Team& operator=(const Team&) = delete;

        Team();

        Team(int id,const sf::Color& color,int gold,book::Game* game);

        void addGold(int amount);
        int getGold()const;

        void addEnemy(Team::type_ptr team);
        const std::vector<Team::type_ptr>& getEnemies()const;

        void  addQgId(std::uint32_t);
        const std::vector<std::uint32_t>& getQgIds()const;
        void removeQgId(std::uint32_t id);

        int id()const;
        const sf::Color& getColor()const;

        void add(book::Client* client);
        void remove(book::Client* client);

        const std::list<book::Client*>& getClients()const;

        bool isGameOver()const;


    private:
        bool _isAlive;
        orm::IntegerField _id;
        int _gold;
        std::vector<std::uint32_t> _QGId;
        sf::Color _color;
        book::Game* _game;

        std::vector<Team::type_ptr> _enemies;
        std::list<book::Client*> _clients;

        MAKE_STATIC_COLUMN(_id)

};

#endif
