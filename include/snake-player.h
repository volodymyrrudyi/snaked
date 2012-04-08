/*  
	Copyright (c) 2012 Volodymyr Rudyi <vladimir.rudoy@gmail.com>

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
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
