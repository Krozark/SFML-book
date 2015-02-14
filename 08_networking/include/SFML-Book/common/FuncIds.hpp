#ifndef BOOK_FUNCIDS_HPP
#define BOOK_FUNCIDS_HPP

namespace book
{
    namespace FuncIds{
        enum FUNCIDS {
            //specials
            IdHandler = 0,
            IdDisconnected,

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
            IdHittedEntity, //server
            IdHitEntity, //server
            IdUpdateTeam, //server
        };
    }

    namespace EntityType {
        enum TYPES {
            IdMain = 0,
            IdEye,
            IdWormEgg,
            IdWorm,
            IdCarnivor
        };
    }
}

#endif
