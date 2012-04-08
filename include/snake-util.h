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
#ifndef __SNAKE_UTIL_H
#define __SNAKE_UTIL_H

#include <stdint.h>
#include <memory.h>
#include <stdlib.h>
#include "snake-types.h"


typedef void (*free_func)(void *);

#define FREE_FUNC(x) (free_func)x

struct _List
{
	void* data;
	List* next;
};

/*
 * Appends new element to list
 */
List* 
list_append(List* head, void *data);

/*
 * Removed element from list
 */
List* 
list_remove(List* head, void *data);

/*
 * Removes all elements from list(clears it)
 */
List* 
list_remove_all(List* head);

/*
 * Removes element from list and frees its data
 */
List* 
list_free(List* head, void *data);

/*
 * Removes element from list and frees its data with given destructor
 */
List* 
list_free_with(List* head, void *data, free_func f);

/*
 * Removes all elements and frees their data
 */
List* 
list_free_all(List* head);

/*
 * Removes all elements and frees their data with given destructor
 */
List* 
list_free_all_with(List* head, free_func f);

/*
 * Finds element in a list and returns pointer to it
 */
List* 
list_find(List* head, void *data);

/*
 * Iterates over the list to get its length
 */
uint32_t 
list_length(List *head);

#endif
