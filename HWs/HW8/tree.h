#pragma once

typedef enum { Ok, MemoryAllocationError } Error;

typedef struct Tree Tree;

Tree *insert(Tree *root, char *key, char *value);

// Deletes an element by key, if there is no such key, does nothing
void deleteElement(Tree **tree, int key);

// Returns a value by key, if there is no such key, returns NULL
char *getValue(Tree *tree, char *key);

// Tree output by direct traversal
void printTree(Tree *root);

// Frees up all the memory allocated for the tree
void freeTree(Tree *root);