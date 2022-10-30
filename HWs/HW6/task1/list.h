#pragma once

typedef int Error;
typedef int Value;

typedef struct Node Node;
typedef struct List List;

List *listCreate();

Error addElement(List *list, Value value);

Error pop(List *list, Value value);

Error printList(List *list);

void freeList(List *list);