#pragma once

#include <stdio.h>

typedef struct Tree Tree;

int fillTree(Tree **root, FILE *fileName);

void printExpression(Tree *tree);

// Tree output by direct traversal
void printTree(Tree *root);

// Frees up all the memory allocated for the tree
void freeTree(Tree **root);