#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Number;
typedef int Error;

typedef struct Node
{
    Number number;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
    Node *tail;
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

Error push(List *list, Number number)
{
    if (list == NULL)
    {
        return -1;
    }

    Node *newElement = calloc(1, sizeof(Node));
    if (newElement == NULL)
    {
        return -2;
    }
    newElement->number = number;

    if (list->head == NULL)
    {
        list->head = newElement;
        newElement->next = list->head;
        list->tail = newElement;
        return 0;
    }

    newElement->next = list->head;
    list->tail->next = newElement;
    list->tail = newElement;
    return 0;
}

Error pop(List *list, Number number, Number *poppedNumber)
{
    if (list == NULL)
    {
        return -1;
    }

    int position = 0;
    Node *currentElement = list->head;
    Node *previousElement = NULL;
    while (position != number)
    {
        previousElement = currentElement;
        currentElement = currentElement->next;
        position++;
    }

    if (currentElement == list->head) // First number
    {
        list->tail->next = list->head->next;
        list->head = list->head->next;
    }
    else if (currentElement == list->tail) // Last number
    {
        list->tail = previousElement;
        list->tail->next = list->head;
    }
    else
    {
        previousElement->next = currentElement->next; // In the middle
    }

    *poppedNumber = currentElement->number;
    free(currentElement);
    return 0;
}

bool isOneElementLeft(List *list)
{
    return list->head != NULL && list->head == list->head->next;
}

Error printList(List *list)
{
    if (list == NULL)
    {
        return -1;
    }
    if (list->head == NULL)
    {
        return 0;
    }

    Node *currentElement = list->head;
    while (currentElement->next != list->head)
    {
        printf("%d ", currentElement->number);
        currentElement = currentElement->next;
    }
    printf("%d\n", currentElement->number);
    return 0;
}

void freeList(List *list)
{
    if (list == NULL)
    {
        return;
    }

    Node *currentElement = list->head;
    while (currentElement != list->tail)
    {
        list->head = list->head->next;
        free(currentElement);
        currentElement = list->head;
    }
    free(currentElement);
    free(list);
}