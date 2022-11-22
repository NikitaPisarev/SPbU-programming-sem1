#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

List *findNode(List **list, Value value)
{
    if (list == NULL)
    {
        return NULL;
    }

    while (*list != NULL && strcmp((*list)->value, value) != 0)
    {
        list = &(*list)->next;
    }
    return *list;
}

Error addNode(List **list, Value value)
{
    if (list == NULL)
    {
        return -1;
    }

    while (*list != NULL)
    {
        list = &(*list)->next;
    }

    List *newNode = calloc(1, sizeof(List));
    if (newNode == NULL)
    {
        return -2;
    }
    newNode->value = calloc(strlen(value) + 1, sizeof(char));
    if (newNode->value == NULL)
    {
        return -2;
    }
    strcpy(newNode->value, value);
    newNode->amount = 1;
    *list = newNode;
    return 0;
}

void printList(List *list)
{
    if (list == NULL)
    {
        return;
    }
    while (list != NULL)
    {
        printf("| ");
        printf("%s %d | ", list->value, list->amount);
        list = list->next;
    }
    printf("\n");
}

void freeList(List *list)
{
    if (list == NULL)
    {
        return;
    }

    freeList(list->next);
    free(list->value);
    free(list);
}