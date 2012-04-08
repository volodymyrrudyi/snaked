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
list_free_all(List* head)
{
	while((head = list_free(head, head->data)));
	
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
