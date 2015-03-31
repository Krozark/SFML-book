#ifndef BOOK_TEAM_HPP
#define BOOK_TEAM_HPP

#include <vector>
#include <list>
#include <cstdint>

#include <SFML/Graphics.hpp>

#include <ORM/fields.hpp>
#include <ORM/fields/ManyToMany.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-Book/server/Game.hpp>

namespace book
{
    class Client;
}

class Team : public orm::SqlObject<Team>
{
    public:
        Team(const Team&) = delete;
        Team& operator=(const Team&) = delete;

        Team();

        Team(int id,const sf::Color& color,int gold,Game::type_ptr game);

        void addGold(int amount);
        int getGold()const;

        void addEnemy(Team::type_ptr team);
        const Team::result_type getEnemies();

        void  addQgId(std::uint32_t);
        const std::vector<std::uint32_t>& getQgIds()const;
        void removeQgId(std::uint32_t id);

        int id()const;
        const sf::Color& getColor()const;

        void add(book::Client* client);
        void remove(book::Client* client);

        const std::list<book::Client*>& getClients()const;

        bool isGameOver()const;

        MAKE_STATIC_COLUMN(_id,_isAlive,_gold,_game,_colorChar)


    private:
        orm::BooleanField _isAlive;
        orm::IntegerField _id;
        orm::IntegerField _gold;
        orm::CharField<4> _colorChar; 

        std::vector<std::uint32_t> _QGId;
        sf::Color _color;

        orm::FK<Game> _game;

        orm::ManyToMany<Team,Team> _enemies;

        std::list<book::Client*> _clients;
        
        virtual void after_load() override;
        virtual void before_save() override;
        virtual void before_update() override;


};

#endif
