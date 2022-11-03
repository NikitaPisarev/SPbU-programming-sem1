#pragma once

typedef int Error;

typedef struct List List;

// Fills the list with data from the "fileName" file
Error fillList(List **list, char *fileName);

// Merge sort in ascending order by "key"
void mergeSorting(List **list, int key);

// List output (if it is empty, it will simply wrap the line)
void printList(List *list);

// Frees up all the memory allocated for the list
void freeList(List **list);

// Error codes:
//  -1: File opening error
//  -2: Memory allocation error