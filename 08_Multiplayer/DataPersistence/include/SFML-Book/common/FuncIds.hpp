#ifndef BOOK_FUNCIDS_HPP
#define BOOK_FUNCIDS_HPP

#include <string>
#include <SFML-Book/common/Configuration.hpp>

namespace book
{
    namespace FuncIds{
        enum FUNCIDS {
            //specials
            IdHandler = 0,
            IdDisconnected,
            IdLogOut,

            //main menu
            IdGetListGame, //client
            IdSetListGame, //server
            IdCreateGame, //client
            IdJoinGame, //client
            IdJoinGameConfirmation, //server
            IdJoinGameReject, //server

            //in game
            IdRequestCreateEntity, //client
            IdRequestDestroyEntity, //client
            IdDestroyEntity, //server
            IdCreateEntity, //server
            IdUpdateEntity, //server
            //// Entity Event
            IdOnHittedEntity, //server
            IdOnHitEntity, //server
            IdOnSpawnEntity, //server
            //// Team event
            IdUpdateTeam, //server
        };
    }

    namespace EntityType {
        enum TYPES {
            IdMain = 0,
            IdEye,
            IdWormEgg,
            IdWorm,
            IdCarnivor,
        };

        struct Info {
            int cost;
            std::string name;
            short int makeAs;
            int icon_id;
            int animation_id;
            std::string description;
        };

        static Info informations[] = {
            {5000, "GQ",IdMain, Configuration::TexBuildMain, Configuration::AnimMainStand,"Main building.\nGenerates gold.\nYou loose the game\nif you don't control\nany one of them."},
            {250, "Worm Egg",IdWormEgg,Configuration::TexBuildWormEgg, Configuration::AnimWormEggStand, "Spawn some worms"},
            {300, "Carnivor",IdCarnivor, Configuration::TexBuildCarnivor, Configuration::AnimCarnivorStand, "Make hight damage"}
        };
    }

}

#endif
