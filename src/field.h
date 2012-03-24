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
#endif
