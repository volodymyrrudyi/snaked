#ifndef __GAME_H
#define __GAME_H

#include <stdlib.h>
#include <memory.h>
#include "snake-types.h"
#include "snake-field.h"
#include "snake-player.h"

/*
    Action contains information about events that are received from the user.
    According to the received action, user can change it's position or exit game.
*/
struct _Action
{
    ActionType type;
    /* Amount of bytes in data buffer*/
    uint32_t data_size;
    char *data;
};

/*
    Game object that stores all information about specified game. This info
    includes field and players. All interaction with current snake should be
    done via game object methods.
*/
struct _Game
{
    Field *field;
    Player **players;
    uint16_t player_count;
};

/*
    Runs in separate process for each game.
*/
void
game_init();

/*
    Creates new game with specified sizes of field.
*/
Game*
game_create(uint16_t width, uint16_t height);

/*
    Creates new player with specified nickname and returns pointer to
    created player object.
*/
Player*
game_add_player(Game *game, const char *nickname);

/*
    Disposes game object and frees all resources.
*/
void
game_dispose(Game* game);

/*
    Callback that is called every time game need to handle player action.
*/
void
game_process_player_action(Game *game, Player *player, Action* action);


#endif
