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
#include "snake-section.h"

SnakeSection*
snake_create(uint16_t x, uint16_t y, Direction direction)
{
    SnakeSection *head = (SnakeSection*)malloc(sizeof(SnakeSection));
    SnakeSection *last;
    int sections;
    head->prev = NULL;
    head->next = NULL;
    head->direction = direction;
    head->x = x;
    head->y = y;
    if (head == NULL)
    {
        SNAKE_ERROR("Can't allocate memory for snake head");
        return NULL;
    }

    last = head;
    for(sections = 0; sections < INITIAL_SNAKE_SIZE; sections++)
    {
        SnakeSection *section = (SnakeSection*)malloc(sizeof(SnakeSection));
        if (section == NULL)
        {
			int i;
            SNAKE_ERROR("Can't allocate memory for snake section. \
                    Deallocating %d sections", sections);
            last = head;
            for(i = 0; i < sections; i++)
            {
                SnakeSection *tmp = last;
                last = last->next;
                free(tmp);
            }

            return NULL;
        }
        last->next = section;
        section->prev = last;
        section->direction = last->direction;
        section->x = snake_section_get_next_x(last);
        section->y = snake_section_get_next_y(last);
        last = section;
    }

    last->next = NULL;

    return head;
}

SnakeSection*
snake_expand(SnakeSection *head, uint16_t amount)
{
    SnakeSection *current = head;
    while(current->next != NULL)
        current = current-> next;

    SnakeSection *section  = (SnakeSection*)malloc(sizeof(SnakeSection));
    section->next = NULL;
    section->prev = current;
    current->next = section;


    return head;
}

void
snake_dispose(SnakeSection *head)
{
    SnakeSection *current = head;
    while(current != NULL)
    {
        SnakeSection *tmp = current;
        current = current->next;
        free(tmp);
    }

}

void
update_snake_position(SnakeSection *head)
{
    SnakeSection *current = head;
    while(current->next != NULL)
    {
        current->x = snake_section_get_next_x(current);
        current->y = snake_section_get_next_y(current);
        current = current->next;
    }

    while(current->prev != NULL)
    {
        current->direction = snake_section_get_next_direction(current);
        current = current->prev;
    }

}

uint16_t
snake_section_get_next_x(SnakeSection *section)
{
    uint16_t next_x = section->x;
    switch(section->direction)
    {
        case Left:
            next_x -= 1;
            break;
        case Right:
            next_x += 1;
            break;
        default:
            break;
    }

    return next_x;
}

uint16_t
snake_section_get_next_y(SnakeSection *section)
{
    uint16_t next_y = section->y;
    switch(section->direction)
    {
        case Up:
            next_y -= 1;
            break;
        case Down:
            next_y += 1;
            break;
        default:
            break;
    }

    return next_y;
}

Direction
snake_section_get_next_direction(SnakeSection *section)
{
    Direction next_direction;
    if (section->prev != NULL)
    {
        next_direction = section->prev->direction;
    } else
    {
        next_direction = section->direction;
    }

    return next_direction;
}



