#pragma once

typedef int Error;

typedef struct List List;

Error fillList(List **list, char *fileName);

void mergeSorting(List **list, int key);

void printList(List *list);

void freeList(List **list);