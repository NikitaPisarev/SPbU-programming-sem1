#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maximumSize 256

typedef int Error;

typedef struct List
{
    char name[maximumSize];
    char number[maximumSize];
    struct List *next;
} List;

Error fillList(List **list, char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL || feof(file))
    {
        return -1;
    }

    char name[maximumSize] = {0};
    char number[maximumSize] = {0};
    while (!feof(file))
    {
        fscanf(file, "%s", name);
        fscanf(file, "%s", number);
        List *person = calloc(1, sizeof(List));
        if (person == NULL)
        {
            fclose(file);
            return -2;
        }
        strcpy(person->name, name);
        strcpy(person->number, number);
        person->next = (*list);
        (*list) = person;
    }
    fclose(file);
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
    (*resultList) = NULL;
    if (leftList == NULL)
    {
        (*resultList) = rightList;
        return;
    }
    if (rightList == NULL)
    {
        (*resultList) = leftList;
        return;
    }

    if (compare(leftList, rightList, key) < 0)
    {
        (*resultList) = leftList;
        leftList = leftList->next;
    }
    else
    {
        (*resultList) = rightList;
        rightList = rightList->next;
    }

    List *headResultList = (*resultList);

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
        (*resultList) = (*resultList)->next;
    }

    while (rightList != NULL)
    {
        (*resultList)->next = rightList;
        rightList = rightList->next;
        (*resultList) = (*resultList)->next;
    }

    (*resultList) = headResultList;
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
            fastPointer = fastPointer->next; // If the list is odd, then slow Pointer will be exactly in the middle of the list,
            slowPointer = slowPointer->next; // and if the list is even, then slowPointer will be one element further
        }
    }

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
    free((*list));
}