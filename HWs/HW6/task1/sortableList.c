#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sortableList.h"

typedef int Error;
typedef int Value;

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
    if (previousElement == NULL) // if a minimal element has been added
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

Error deleteElement(List *list, Value value)
{
    if (list == NULL)
    {
        return -1;
    }

    Node *currentElement = list->head;
    if (currentElement == NULL)
    {
        return -3;
    }
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
    free(currentElement);
    return 0;
}

Error printList(List *list)
{
    if (list == NULL)
    {
        return -1;
    }

    printf("[ ");
    Node *currentElement = list->head;
    while (currentElement != NULL)
    {
        printf("%d ", currentElement->value);
        currentElement = currentElement->next;
    }
    printf("]\n");
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

bool testAdd()
{
    List *list = listCreate();
    if (list == NULL)
    {
        return false;
    }

    addElement(list, 10);
    bool testFlag1 = list->head->value == 10;

    addElement(list, 2);
    bool testFlag2 = list->head->value == 2 && list->head->next->value == 10;

    addElement(list, 7);
    bool testFlag3 = list->head->value == 2 && list->head->next->value == 7 &&
                     list->head->next->next->value == 10;

    freeList(list);
    return testFlag1 && testFlag2 && testFlag3;
}

bool testDelete()
{
    List *list = listCreate();
    if (list == NULL)
    {
        return false;
    }

    list->head = calloc(1, sizeof(Node));
    if (list->head == NULL)
    {
        return false;
    }
    list->head->value = 10;

    list->head->next = calloc(1, sizeof(Node));
    if (list->head->next == NULL)
    {
        return false;
    }
    list->head->next->value = 20;

    list->head->next->next = calloc(1, sizeof(Node));
    if (list->head->next->next == NULL)
    {
        return false;
    }
    list->head->next->next->value = 30;

    deleteElement(list, 20);
    bool testFlag1 = list->head->value == 10 && list->head->next->value == 30;

    deleteElement(list, 10);
    bool testFlag2 = list->head->value == 30;

    bool testFlag3 = deleteElement(list, 50) == -3;

    deleteElement(list, 30);
    bool testFlag4 = list->head == NULL;

    bool testFlag5 = deleteElement(list, 30) == -3;
    freeList(list);
    return testFlag1 && testFlag2 && testFlag3 && testFlag4 && testFlag5;
}

bool tests()
{
    return testAdd() && testDelete();
}