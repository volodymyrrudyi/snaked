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
