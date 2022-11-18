#pragma once

typedef enum { Ok, MemoryAllocationError } Error;

typedef struct Tree Tree;

Tree *addValue(Tree *tree, char *key, char *value);

// Deletes an element by key, if there is no such key, does nothing
Tree *deleteElement(Tree *tree, char *key);

// Returns a value by key, if there is no such key, returns NULL
char *getValue(Tree *tree, char *key);

// Tree output by direct traversal
void printTree(Tree *root);

// Frees up all the memory allocated for the tree
void freeTree(Tree *root);