#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mergeSortingList.h"

#define maximumSize 256
#define firstDiscount 0.5
#define secondDiscount 0.25

typedef int Error;

typedef struct List
{
    char name[maximumSize];
    int amount;
    struct List *next;
} List;

Error addElement(List **list, char *name, int amount)
{
    List *product = calloc(1, sizeof(List));
    if (product == NULL)
    {
        return -2;
    }
    strcpy(product->name, name);
    product->amount = amount;
    product->next = *list;
    *list = product;
    return 0;
}

int compare(List *firstElement, List *secondElement, int key)
{
    if (key >= 0)
    {
        return strcmp(firstElement->name, secondElement->name);
    }
    return secondElement->amount - firstElement->amount; // It turns out that it sorts the numbers in descending order,
} // and the names in ascending order.

void merge(List *leftList, List *rightList, List **resultList, int key)
{
    *resultList = NULL;
    if (leftList == NULL)
    {
        *resultList = rightList;
        return;
    }
    if (rightList == NULL)
    {
        *resultList = leftList;
        return;
    }

    if (compare(leftList, rightList, key) < 0)
    {
        *resultList = leftList;
        leftList = leftList->next;
    }
    else
    {
        *resultList = rightList;
        rightList = rightList->next;
    }

    List *headResultList = *resultList;

    while (leftList != NULL && rightList != NULL)
    {
        if (compare(leftList, rightList, key) < 0)
        {
            (*resultList)->next = leftList;
            leftList = leftList->next;
        }
        else
        {
            (*resultList)->next = rightList;
            rightList = rightList->next;
        }
        (*resultList) = (*resultList)->next;
    }

    while (leftList != NULL)
    {
        (*resultList)->next = leftList;
        leftList = leftList->next;
        *resultList = (*resultList)->next;
    }

    while (rightList != NULL)
    {
        (*resultList)->next = rightList;
        rightList = rightList->next;
        *resultList = (*resultList)->next;
    }

    *resultList = headResultList;
}

void splitList(List *list, List **leftList, List **rightList)
{
    if (list == NULL || list->next == NULL)
    {
        (*leftList) = list;
        (*rightList) = NULL;
        return;
    }

    List *fastPointer = list->next;
    List *slowPointer = list;
    while (fastPointer != NULL)
    {
        fastPointer = fastPointer->next;
        if (fastPointer != NULL)
        {
            fastPointer = fastPointer->next; // If the list is even, then slowPointer will point to the "LengthList"/2 - 1 index,
            slowPointer = slowPointer->next; // so it will divide the list in two,
        }                                    // and if the list is odd, then slowPointer will point exactly to the middle,
    }                                        // so the left list will be 1 more than the right

    (*leftList) = list;
    (*rightList) = slowPointer->next;
    slowPointer->next = NULL;
}

void mergeSorting(List **list, int key)
{
    if (*list == NULL || (*list)->next == NULL)
    {
        return;
    }

    List *leftList = NULL;
    List *rightList = NULL;

    splitList((*list), &leftList, &rightList);
    mergeSorting(&leftList, key);
    mergeSorting(&rightList, key);

    merge(leftList, rightList, list, key);
}

void findingAndPrintingtheFirstDiscount(List **list, int amount)
{
    if (*list == NULL)
    {
        return;
    }
    mergeSorting(list, -1); // Sort descending by amount
    while (amount != 0 && *list != NULL)
    {
        printf("%s\t%.1f", (*list)->name, (*list)->amount * firstDiscount);
        List *deleteElement = *list;
        (*list) = (*list)->next;
        free(deleteElement);
        --amount;
    }
}

void findingAndPrintingtheSecondDiscount(List **list, int amount)
{
    if (*list == NULL)
    {
        return;
    }
    mergeSorting(list, 0); // Sort ascending by name
    while (amount != 0 && *list != NULL)
    {
        printf("%s\t%.1f", (*list)->name, (*list)->amount * secondDiscount);
        List *deleteElement = (*list);
        (*list) = (*list)->next;
        free(deleteElement);
        --amount;
    }
}

void printList(List *list)
{
    while (list != NULL)
    {
        printf("%s\t%d", list->name, list->amount);
        list = list->next;
    }
    printf("\n");
}

void freeList(List **list)
{
    List *deleteElement = NULL;
    while ((*list) != NULL)
    {
        deleteElement = (*list);
        (*list) = (*list)->next;
        free(deleteElement);
    }
    free(*list);
}