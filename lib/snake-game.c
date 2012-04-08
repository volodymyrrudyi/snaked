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
#include "snake-game.h"

void*
game_init(void *arg)
{
	return NULL;
}

Game*
game_create(uint16_t width, uint16_t height)
{
    Game* new_game = (Game*)malloc(sizeof(Game));
    new_game->players = NULL;
    new_game->field = field_create(width, height);
    return new_game;
}

void
game_dispose(Game* game)
{
	list_free_all_with(game->players, FREE_FUNC(player_dispose));
    free(game);
}

void
game_update(Game *game, UpdateType type, void *args)
{
}
