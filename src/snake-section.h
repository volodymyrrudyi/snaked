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
#ifndef __SNAKE_SECTION_H
#define __SNAKE_SECTION_H

#include <stdlib.h>

#include "snake-types.h"
#include "snake-log.h"
#define INITIAL_SNAKE_SIZE 2


struct _SnakeSection
{
   uint16_t x;
   uint16_t y;
   Direction direction;
   struct _SnakeSection* prev;
   struct _SnakeSection* next;
};

SnakeSection*
snake_create(uint16_t x, uint16_t y, Direction direction);

SnakeSection*
snake_expand(SnakeSection *head, uint16_t amount);

void
snake_update_position(SnakeSection *head);

void
snake_dispose(SnakeSection *head);

uint16_t
snake_section_get_next_x(SnakeSection *section);

uint16_t
snake_section_get_next_y(SnakeSection *section);

Direction
snake_section_get_next_direction(SnakeSection *section);


#endif
