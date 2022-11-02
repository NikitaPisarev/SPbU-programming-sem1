#pragma once

typedef int Error;

typedef struct Person Person;

// Creating a list
Error listCreate(Person **list);

// If the list is created, adds the value to the sortable list
Error fillList(Person **list, char *fileName);

// If a list is created, outputs it
Error printList(Person **list);

// Frees up all the memory allocated for the list
void freeList(Person *list);

// Error codes:
//  -1: Person not created
//  -2: Memory allocation error
//  -3: No such value found