#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct Node
{
    Value value;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
} List;

List *listCreate()
{
    List *list = calloc(1, sizeof(List));
    if (list == NULL)
    {
        return NULL;
    }
    return list;
}

Error addElement(List *list, Value value)
{
    if (list == NULL)
    {
        return -1;
    }

    Node *currentElement = list->head;
    Node *previousElement = NULL;
    while (currentElement != NULL && currentElement->value < value)
    {
        previousElement = currentElement;
        currentElement = currentElement->next;
    }
    Node *newElement = calloc(1, sizeof(Node));
    if (newElement == NULL)
    {
        return -2;
    }
    if (previousElement == NULL)
    {
        list->head = newElement;
    }
    else
    {
        previousElement->next = newElement;
    }
    newElement->next = currentElement;
    newElement->value = value;
    return 0;
}

Error deleteElement(List *list, int index, int *value)
{
    if (list == NULL)
    {
        return -1;
    }

    int counter = 0;

    Node *currentElement = list->head;
    Node *previousElement = NULL;
    while (counter != index && currentElement->next != NULL)
    {
        previousElement = currentElement;
        currentElement = currentElement->next;
        ++counter;
    }
    if (counter != index || currentElement == NULL) // Second condition for an empty list
    {
        return -3;
    }

    if (previousElement == NULL) // If this is the first element
    {
        list->head = currentElement->next;
    }
    else
    {
        previousElement->next = currentElement->next;
    }
    *value = currentElement->value;
    free(currentElement);
    return 0;
}

Error printList(List *list)
{
    if (list == NULL)
    {
        return -1;
    }

    Node *currentElement = list->head;
    while (currentElement != NULL)
    {
        printf("%d ", currentElement->value);
        currentElement = currentElement->next;
    }
    printf("\n");
    return 0;
}

void freeList(List *list)
{
    if (list == NULL)
    {
        return;
    }

    Node *currentElement = list->head;
    Node *previousElement = currentElement;
    while (currentElement != NULL)
    {
        currentElement = currentElement->next;
        free(previousElement);
        previousElement = currentElement;
    }
    free(list);
}