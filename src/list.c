#include "../header/list.h"

struct Element
{
	void* data;
	struct Element* next;
};

struct List
{
	struct Element* first;
	uint element_size;
	uint length;
};


list list_init(uint size)
{
	list l = malloc(sizeof(struct List));
	if (!l)
	{
		fprintf(stderr, "Error during memory allocation !\n");
		return 0;
	}
	l->first = 0;
	l->element_size = size;
	l->length = 0;
	return l;
}

void* list_get(list l, uint index)
{
	if (index >= l->length)
	{
		return 0;
	}
	struct Element* current = l->first;
	for (uint i = 0; i < index; i++)
	{
		current = current->next;
	}
	return current->data;
}

uint list_length(list l)
{
	return l->length;
}

void list_add(list l, void* data, int index)
{
	struct Element* new_element = malloc(sizeof(struct Element));
	if (!new_element)
	{
		fprintf(stderr, "Error during memory allocation !\n");
		return;
	}
	new_element->data = data;
	if (index == -1)
	{
		list_add(l, data, l->length);
	}
	else
	{

		if (l->first == NULL)
		{
			l->first = new_element;
		}
		else {
			struct Element* current = l->first;
			for (uint i = 0; i < index - 1; i++)
			{
				current = current->next;
			}
			new_element->next = current->next;
			current->next = new_element;
		}
		l->length++;
	}

}

void list_remove(list l, void* data)
{
	struct Element* current = l->first;
	struct Element* previous = 0;
	while (current)
	{
		if (current->data == data)
		{
			if (previous)
			{
				previous->next = current->next;
			}
			else
			{
				l->first = current->next;
			}
			free(current);
			l->length--;
			return;
		}
		previous = current;
		current = current->next;
	}
}

void list_free(list l)
{
	struct Element* current = l->first;
	while (current)
	{
		struct Element* next = current->next;
		free(current);
		current = next;
	}
	free(l);
}
