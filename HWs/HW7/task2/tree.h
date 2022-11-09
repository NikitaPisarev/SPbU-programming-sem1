#pragma once

#include <stdio.h>

typedef enum { Ok, MemoryAllocationError } Error;

typedef struct Tree Tree;

// Fills in the tree from the file "fileName"
// Returns:
// Ok - if everything is ok;
// MemoryAllocationError - if a memory allocation error occurred
Error fillTree(Tree **root, FILE *fileName);

// Outputs the expression stored in the tree
void printExpression(Tree *tree);

// Calculates the value of the expression in the tree
int evaluateTree(Tree *tree);

// Frees up all the memory allocated for the tree
void freeTree(Tree **root);