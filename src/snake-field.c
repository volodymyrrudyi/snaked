#include "snake-field.h"

Field*
field_create(uint16_t width, uint16_t height)
{
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

    for(int col = 0; col < width; col++)
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
