#ifndef __GAME_H
#define __GAME_H

#include <stdlib.h>
#include <memory.h>
#include "snake-types.h"
#include "field.h"
#include "player.h"

struct _Action
{
    ActionType type;
    char *data;
};
struct _Game
{
    Field *field;
    Player *players;
    uint16_t player_count;
};

Game*
game_create();

void
game_add_player(Game *game, Player *player);

void
game_dispose(Game* game);

void
game_process_player_action(Game *game, Player *player, Action* action);


#endif
