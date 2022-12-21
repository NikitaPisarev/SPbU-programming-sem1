#pragma once

#include <stdbool.h>

typedef int Error;

typedef struct List List;

// Adds an element to the list
Error addElement(List **list, char *name, int amount);

// Merge sort in ascending order by "key"
void mergeSorting(List **list, int key);

// List output (if it is empty, it will simply wrap the line)
void printList(List *list);

// Frees up all the memory allocated for the list
void freeList(List **list);

// We are looking for AMOUNT products with the largest number of output and delete them
void findingAndPrintingtheFirstDiscount(List **list, int amount);

// We are looking for AMOUNT products in lexicographic order, displaying and deleting them
void findingAndPrintingtheSecondDiscount(List **list, int amount);

// Error codes:
//  -2: Memory allocation error