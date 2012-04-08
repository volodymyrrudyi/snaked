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
#include "snake-util.h"

List* 
list_append(List* head, void *data)
{
	List *current = NULL;
	List *new_element = (List*)malloc(sizeof(List));
	new_element->data = data;
	new_element->next = NULL;
	
	if (head == NULL)
	{
		return new_element;
	} else
	{
		current = head;
		while(current->next)
		{
			current = current->next;
		}
		
		current->next = new_element;
	}
	
	return head;
}

List* 
list_remove(List* head, void *data)
{
	List *current = NULL;
	List *previous = NULL;
	
	if (head == NULL)
	{
		return NULL;
	}
	
	current = head;
	
	while(current->data != data)
	{
		previous = current;
		current = current->next;
	}
	
	if (current == NULL)
	{
		return head;
	} 
	else if (current == head)
	{
		head = current->next;
	}else
	{
		previous->next = current->next;

	}
	free(current);	
	return head;
}


List* 
list_remove_all(List* head)
{
	while((head = list_remove(head, head->data)));
	
	return NULL;
}

List* 
list_free(List* head, void *data)
{
	List *current = NULL;
	List *previous = NULL;
	
	if (head == NULL)
	{
		return NULL;
	}
	
	current = head;
	
	while(current->data != data)
	{
		previous = current;
		current = current->next;
	}
	
	if (current == NULL)
	{
		return NULL;
	} 
	else if (current == head)
	{
		head = current->next;
	}else
	{
		previous->next = current->next;
	}
	
	free(current->data);
	free(current);
	return head;
}

List* 
list_free_with(List* head, void *data, free_func f)
{
	List *current = NULL;
	List *previous = NULL;
	
	if (head == NULL)
	{
		return NULL;
	}
	
	current = head;
	
	while(current->data != data)
	{
		previous = current;
		current = current->next;
	}
	
	if (current == NULL)
	{
		return NULL;
	} 
	else if (current == head)
	{
		head = current->next;
	}else
	{
		previous->next = current->next;
	}
	
	f(current->data);
	free(current);
	return head;
}

List* 
list_free_all(List* head)
{
	while((head = list_free(head, head->data)));
	
	return NULL;
}

List* 
list_free_all_with(List* head, free_func f)
{
	while((head = list_free_with(head, head->data, f)));
	
	return NULL;
}

List* 
list_find(List* head, void *data)
{
	List *current = head;
	
	while(current != NULL)
	{
		if (current->data == data)
		{
			break;
		}
	}
	
	return current;
}

uint32_t 
list_length(List *head)
{
	uint32_t size = 0;
	List *current = head;
	
	while(current != NULL)
	{
		size++;
	}
	
	return size;
}
