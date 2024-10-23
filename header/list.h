#pragma once
#ifndef LIST_HEADER
#define LIST_HEADER
#include <stdlib.h>
#include <stdio.h>
struct List;
typedef struct List* list;
typedef unsigned int uint;

list list_init(uint size);
#define list_create(e) list_init(sizeof(e))
void* list_get(list l, uint index);
uint list_length(list l);
//Add an element to the list at the specified index -1 to add at the end
void list_add(list l, void* data,int index);
//Remove the first occurence of one element from the list
void list_remove(list l, void* data);
//Free the list
void list_free(list l);


#endif // ! LIST_HEADER