#include <stdio.h>
#include <stdlib.h>
#include "set.h"

typedef struct Node
{
    Value value;
    struct Node *next;
} Node;

typedef struct Set
{
    Node *head;
} Set;

Set *setCreate()
{
    Set *set = calloc(1, sizeof(Set));
    return set;
}

Error addElement(Set *set, Value value)
{
    if (set == NULL)
    {
        return -1;
    }

    Node *currentElement = set->head;
    Node *previousElement = NULL;
    while (currentElement != NULL && currentElement->value < value)
    {
        previousElement = currentElement;
        currentElement = currentElement->next;
    }
    if (currentElement == NULL || currentElement->value > value)
    {
        Node *newElement = calloc(1, sizeof(Node));
        if (newElement == NULL)
        {
            return -2;
        }
        if (previousElement == NULL)
        {
            set->head = newElement;
        }
        else
        {
            previousElement->next = newElement;
        }
        newElement->next = currentElement;
        newElement->value = value;
    }
    return 0;
}

Error setUnion(Set *firstSet, Set *secondSet, Set *unionSet)
{
    if (firstSet == NULL || secondSet == NULL || unionSet == NULL)
    {
        return -1;
    }

    Node *currentElement = firstSet->head;
    int errorCode = 0;
    while (currentElement != NULL)
    {
        errorCode = addElement(unionSet, currentElement->value);
        if (errorCode != 0)
        {
            return errorCode;
        }
        currentElement = currentElement->next;
    }
    currentElement = secondSet->head;
    while (currentElement != NULL)
    {
        errorCode = addElement(unionSet, currentElement->value);
        if (errorCode != 0)
        {
            return errorCode;
        }
        currentElement = currentElement->next;
    }
    return 0;
}

Error printSet(Set *set)
{
    if (set == NULL)
    {
        return -1;
    }

    Node *currentElement = set->head;
    printf("[ ");
    while (currentElement != NULL)
    {
        printf("%d ", currentElement->value);
        currentElement = currentElement->next;
    }
    printf("]\n");
    return 0;
}

void freeSet(Set *set)
{
    if (set == NULL)
    {
        return;
    }

    Node *currentElement = set->head;
    Node *previousElement = currentElement;
    while (currentElement != NULL)
    {
        currentElement = currentElement->next;
        free(previousElement);
        previousElement = currentElement;
    }
    free(set);
}