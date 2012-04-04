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
#ifndef __FIELD_H
#define __FIELD_H

#include <stdlib.h>
#include "snake-types.h"
#include "snake-log.h"

struct _Cell
{
    CellType type;
};

struct _Field
{
    uint16_t width;
    uint16_t height;
    uint16_t player_count;
    Cell **cells;
};

Field*
field_create(uint16_t width, uint16_t height);

CellType
random_cell(Field *field);

void
field_dispose(Field *field);
#endif
