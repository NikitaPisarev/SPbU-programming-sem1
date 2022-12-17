#pragma once

#include <stdbool.h>

typedef int Error;

typedef struct List List;

// Adds an element to the list
Error addElement(List **list, char *name, char *number);

// Merge sort in ascending order by "key"
void mergeSorting(List **list, int key);

// List output (if it is empty, it will simply wrap the line)
void printList(List *list);

// Frees up all the memory allocated for the list
void freeList(List **list);

// Tests for the addElement and mergeSorting functions
// Returns:
// true - tests passed
// false - tests failed
bool tests();

// Error codes:
//  -1: File opening error
//  -2: Memory allocation error