#ifndef BOOK_TEAM_HPP
#define BOOK_TEAM_HPP

#include <vector>
#include <list>

#include <cstdint>

namespace book
{
    class Client;

    class Team
    {
        public:
            Team(const Team&) = delete;
            Team& operator=(const Team&) = delete;

            Team();

            void addGold(int amount);
            void addEnemy(Team* team);
            const std::vector<Team*>& getEnemies()const;

            void  addQgId(std::uint32_t);
            const std::vector<std::uint32_t>& getQgIds()const;
            void removeQgId(std::uint32_t id);

            int id()const;

            void add(Client* client);
            void remove(Client* client);

            const std::list<Client*>& getClients()const;

            bool isAlive;

            static const int MAX_TEAMS = 4;

        private:
            int _id;
            int _gold;
            std::vector<std::uint32_t> _QGId;

            static int _numberOfCreations;

            std::vector<Team*> _enemies;
            std::list<Client*> _clients;


    };
}
#endif
