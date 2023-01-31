#pragma once

#include <stdbool.h>

typedef enum
{
    Ok,
    MemoryAllocationError
} Error;

typedef struct Tree Tree;

// Create empty tree
Tree *createEmptyTree();

// Adds a value by key,
// if such a key already exists, replaces the value with a new one
// Puts it in "errorCode":
// Ok - if everything is ok;
// MemoryAllocationError - if a memory allocation error occurred
Tree *addValue(Tree *tree, char *key, char *value, Error *errorCode);

// Deletes an element by key, if there is no such key, does nothing
Tree *deleteElement(Tree *root, char *key);

// Returns a value by key, if there is no such key, returns NULL
char *getValue(Tree *tree, char *key);

// Tree output by direct traversal
void printTree(Tree *root);

// Frees up all the memory allocated for the tree
void freeTree(Tree *root);

// Tests
// returns: "true" if the tests are passed, otherwise "false"
bool tests();