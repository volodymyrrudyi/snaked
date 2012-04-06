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
#include "snake-field.h"

Field*
field_create(uint16_t width, uint16_t height)
{
	int col;
    Field *field = (Field*)malloc(sizeof(Field));
    field->width = width;
    field->height = height;
    if (field == NULL)
    {
        SNAKE_ERROR("Can't allocate memory for field");
        return NULL;
    }

    field->cells = (Cell**)malloc(sizeof(Cell*)*width);
    if (field->cells == NULL)
    {
        SNAKE_ERROR("Can't allocate memory for cell columns array");
        free(field);
        return NULL;
    }

    for(col = 0; col < width; col++)
    {
        field->cells[col] = (Cell*)malloc(sizeof(Cell)*height);
    }

    return field;
}

void
field_dispose(Field *field)
{
}

CellType
random_cell(Field *field)
{
    return Empty;
}
