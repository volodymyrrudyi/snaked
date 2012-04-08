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
#ifndef __GAME_H
#define __GAME_H

#include <stdlib.h>
#include <memory.h>
#include "snake-types.h"
#include "snake-field.h"
#include "snake-player.h"
#include "snake-util.h"

/*
    Game object that stores all information about specified game. This info
    includes field and players. All interaction with current snake should be
    done via game object methods.
*/
struct _Game
{
    Field *field;
    List *players;  
	/*
		Callback that is called every time game updated according to 
		specified update type and given args. Should be used in 
		presentation layer to update screen/etc
	*/
	void (*game_updated_cb)(Game*, Player*, UpdateType, void*);
};

/*
    Runs in separate thread for each game.
    Argument is pointer to Game object
*/
void*
game_init(void *arg);

/*
    Creates new game with specified sizes of field.
*/
Game*
game_create(uint16_t width, uint16_t height);

/*
    Disposes game object and frees all resources.
*/
void
game_dispose(Game* game);

/*
    Callback that is called every time game need to update
*/
void
game_update(Game *game, UpdateType type, void *args);

#endif
