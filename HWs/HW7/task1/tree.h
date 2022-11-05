#pragma once

typedef enum { Ok, MemoryAllocationError } Error;

typedef struct Tree Tree;

// Adds a value by key,
// if such a key already exists, replaces the value with a new one
// Returns:
// Ok - if everything is ok;
// MemoryAllocationError - if a memory allocation error occurred
Error add(Tree **root, int key, char *value);

// Deletes an element by key, if there is no such key, does nothing
void deleteElement(Tree **tree, int key);

// Returns a value by key, if there is no such key, returns NULL
char *getValue(Tree *tree, int key);

// Tree output by direct traversal
void printTree(Tree *root);

// Frees up all the memory allocated for the tree
void freeTree(Tree **root);