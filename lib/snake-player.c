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
#include "snake-player.h"

Player*
create_player(const char* nickname, uint16_t color, uint16_t x,  uint16_t y,
        Direction direction)
{
    Player *player = (Player*)malloc(sizeof(Player));

    if (player == NULL)
    {
        SNAKE_ERROR("Can't allocate memory for new player");
        return NULL;
    }

    player->snake_head = snake_create(x, y, direction);
    if (player->snake_head == NULL)
    {
        SNAKE_ERROR("Can't create snake for player");
        free(player);
        return NULL;
    }

    return player;
}

void
player_change_direction(Player* player, Direction direction)
{
    player->snake_head->direction = direction;
}

void
player_dispose(Player *player)
{
    snake_dispose(player->snake_head);
    free(player->nickname);
    free(player);
}
