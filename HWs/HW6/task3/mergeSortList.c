#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define maximumSize 256

typedef int Error;

typedef struct List
{
    char name[maximumSize];
    char number[maximumSize];
    struct List *next;
} List;

Error addElement(List **list, char *name, char *number)
{
    List *person = calloc(1, sizeof(List));
    if (person == NULL)
    {
        return -2;
    }
    strcpy(person->name, name);
    strcpy(person->number, number);
    person->next = *list;
    *list = person;
    return 0;
}

int compare(List *firstElement, List *secondElement, int key)
{
    if (key >= 0)
    {
        return strcmp(firstElement->name, secondElement->name);
    }
    return strcmp(firstElement->number, secondElement->number);
}

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
    if ((*list) == NULL || (*list)->next == NULL)
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

void printList(List *list)
{
    while (list != NULL)
    {
        printf("%s\t%s\n", list->name, list->number);
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

bool testAdd()
{
    List *list = NULL;
    addElement(&list, "Alex", "+123");
    bool testFlag1 = strcmp(list->name, "Alex") == 0 && strcmp(list->number, "+123") == 0;

    addElement(&list, "Ben", "+321");
    bool testFlag2 = strcmp(list->name, "Ben") == 0 &&
                     strcmp(list->number, "+321") == 0 &&
                     strcmp(list->next->name, "Alex") == 0 &&
                     strcmp(list->next->number, "+123") == 0;

    freeList(&list);
    return testFlag1 && testFlag2;
}

bool testMergeSort()
{
    List *list = calloc(1, sizeof(List));
    if (list == NULL)
    {
        return false;
    }
    strcpy(list->name, "Ben");
    strcpy(list->number, "+123");

    list->next = calloc(1, sizeof(List));
    if (list->next == NULL)
    {
        return false;
    }
    strcpy(list->next->name, "Alex");
    strcpy(list->next->number, "+321");

    list->next->next = calloc(1, sizeof(List));
    if (list->next == NULL)
    {
        return false;
    }
    strcpy(list->next->next->name, "Carl");
    strcpy(list->next->next->number, "+231");

    mergeSorting(&list, 0);
    bool testFlag1 = strcmp(list->name, "Alex") == 0 && strcmp(list->number, "+321") == 0 &&
                     strcmp(list->next->name, "Ben") == 0 && strcmp(list->next->number, "+123") == 0 &&
                     strcmp(list->next->next->name, "Carl") == 0 &&
                     strcmp(list->next->next->number, "+231") == 0;

    mergeSorting(&list, -1);
    bool testFlag2 = strcmp(list->name, "Ben") == 0 && strcmp(list->number, "+123") == 0 &&
                     strcmp(list->next->name, "Carl") == 0 && strcmp(list->next->number, "+231") == 0 &&
                     strcmp(list->next->next->name, "Alex") == 0 &&
                     strcmp(list->next->next->number, "+321") == 0;
    freeList(&list);
    return testFlag1 && testFlag2;
}

bool tests()
{
    return testAdd() && testMergeSort();
}