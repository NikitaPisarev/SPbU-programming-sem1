#pragma once

typedef int Error;
typedef char *Value;

typedef struct List
{
    Value value;
    int amount;
    struct List *next;
} List;

// returns the node by the specified Value, if there is no such returns NULL
List *findNode(List **list, Value value);

// Adds the value to the list
Error addNode(List **list, Value value);

// Outputs a list
void printList(List *list);

// Frees up all the memory allocated for the list
void freeList(List *list);

// Error codes:
//  -1: List not created
//  -2: Memory allocation error