#pragma once

typedef struct Tree Tree;

void add(Tree **root, int key, char *value);

void freeTree(Tree **root);

void printTree(Tree *root);