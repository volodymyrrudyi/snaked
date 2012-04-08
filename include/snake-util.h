#ifndef __SNAKE_UTIL_H
#define __SNAKE_UTIL_H

#include <stdint.h>
#include <memory.h>
#include <stdlib.h>
#include "snake-types.h"

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
 * Removes all elements and frees their data
 */
List* 
list_free_all(List* head);

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
