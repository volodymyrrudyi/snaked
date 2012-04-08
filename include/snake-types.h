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
#ifndef __SNAKE_TYPES_H
#define __SNAKE_TYPES_H

#include <stdint.h>

typedef uint32_t BOOL;
#define TRUE 1
#define FALSE 0

/*
 * Describes type of the update
 */
enum _UpdateType
{
	PlayerRecalculatePosition,	/* Called on timer or request from server */
	PlayerChangedDirection, 	/* Called when some player changed direction */
	PlayerCollectedFruit, 		/* Called when player collected fruit */
	PlayerCollectedBone, 		/* Called when player collected bone of other player */
	PlayerCrashedIntoWall, 		/* Called when player crashed into wall */
	PlayerSyncPosition,			/* Called when server forces to sync player position */
	PlayerSyncPoints, 			/* Called when server wants to update stats */
	FieldSyncSituation,			/* Called when server wants to sync status of field cells */
	GameUpdateState 			/* Called when game state was changed */
};

enum _Direction
{
    Left,
    Right,
    Up,
    Down
};

enum _CellType
{
    Empty,
    Fruit,
    Wall,
    Bone
};


typedef struct _List List;
typedef struct _Game Game;
typedef struct _Field Field;
typedef struct _Cell Cell;
typedef struct _Player Player;
typedef struct _SnakeSection SnakeSection;
typedef enum _UpdateType UpdateType;
typedef enum _CellType CellType;
typedef enum _Direction Direction;

#endif
