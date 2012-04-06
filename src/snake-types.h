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

enum _ActionType
{
    Movement,
    Exit
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


typedef struct _Game Game;
typedef struct _Action Action;
typedef struct _Field Field;
typedef struct _Cell Cell;
typedef struct _Player Player;
typedef struct _SnakeSection SnakeSection;
typedef enum _ActionType ActionType;
typedef enum _CellType CellType;
typedef enum _Direction Direction;

#endif
