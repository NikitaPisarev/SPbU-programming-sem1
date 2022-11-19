#pragma once

typedef int Error;
typedef int Value;

typedef struct List List;

// Creating a list
List *listCreate();

// If the list is created, adds the value to the sortable list
Error addElement(List *list, Value value);

// If there is such an element, deletes it
Error deleteElement(List *list, Value value);

// If a list is created, outputs it
Error printList(List *list);

// Frees up all the memory allocated for the list
void freeList(List *list);

// Error codes:
//  -1: List not created
//  -2: Memory allocation error
//  -3: No such value found