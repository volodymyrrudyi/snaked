#ifndef __GAME_H
#define __GAME_H

#include "snake-types.h"
struct _Game
{
    Field *field;
    Player *players;
};

Game*
game_create();
void
game_add_player(Game *game, Player *player);

void
game_dispose(Game* game);



#endif
