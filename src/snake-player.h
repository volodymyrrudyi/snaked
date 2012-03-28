#ifndef __PLAYER_H
#define __PLAYER_H

#include <stdlib.h>
#include <stdio.h>
#include "snake-types.h"
#include "snake-section.h"
#include "snake-log.h"

struct _Player
{
    char *nickname;
    uint16_t color;
    uint8_t is_alive;
    uint32_t points;
    SnakeSection *snake_head;
};

Player*
player_create(const char* nickname, uint16_t color, uint16_t x,  uint16_t y,
        Direction direction);
void
player_change_direction(Player* player, Direction direction);

void
player_dispose(Player *player);



#endif
