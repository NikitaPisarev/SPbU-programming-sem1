#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

typedef int Error;
typedef char *Value;

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
    if (list->head == NULL)
    {
        list->head = calloc(1, sizeof(Node));
        if (list->head == NULL)
        {
            return -2;
        }
        list->head->value = calloc(strlen(value) + 1, sizeof(char));
        if (list->head->value == NULL)
        {
            return -2;
        }
        strcpy(list->head->value, value);
        return 0;
    }
    Node *currentElement = list->head;
    while (currentElement->next != NULL)
    {
        currentElement = currentElement->next;
    }
    Node *newElement = calloc(1, sizeof(Node));
    if (newElement == NULL)
    {
        return -2;
    }
    newElement->value = calloc(strlen(value) + 1, sizeof(char));
    if (newElement->value == NULL)
    {
        return -2;
    }
    strcpy(newElement->value, value);
    currentElement->next = newElement;
    return 0;
}

Error pop(List *list, Value value)
{
    if (list == NULL)
    {
        return -1;
    }

    Node *currentElement = list->head;
    Node *previousElement = NULL;
    while (currentElement->value != value && currentElement->next != NULL)
    {
        previousElement = currentElement;
        currentElement = currentElement->next;
    }
    if (currentElement->value != value) // No such value was found
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
    free(currentElement->value);
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
        printf("%s ", currentElement->value);
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
        free(previousElement->value);
        free(previousElement);
        previousElement = currentElement;
    }
    free(list);
}