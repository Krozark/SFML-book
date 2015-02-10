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
            //in game
            IdPosition, //server
            IdCreateEntity, //client
            IdDestroyEntity, //client
        };
    }
}

#endif
