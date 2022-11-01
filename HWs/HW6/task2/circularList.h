#pragma once

#include <stdbool.h>

typedef int Number;
typedef int Error;

typedef struct Node Node;
typedef struct List List;

// Creating a list
List *listCreate();

// Adding an element to the end of the list
Error push(List *list, Number number);

// If the list exists, it takes the element under the index "number" and puts its value in "poppedNumber"
Error pop(List *list, Number number, Number *poppedNumber);

// Checks if there is one element in the list
bool isOneElementLeft(List *list);

// If the list exists, then outputs it
Error printList(List *list);

// Frees up all the memory allocated for the list
void freeList(List *list);

//Error codes:
// -1: List not created
// -2: Memory allocation error