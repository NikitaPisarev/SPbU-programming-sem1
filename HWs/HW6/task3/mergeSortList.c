#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergeSortList.h"

#define size 256

typedef int Error;

typedef struct Person
{
    char name[size];
    char number[size];
    struct Person *next;
} Person;

Error listCreate(Person **list)
{
    *list = calloc(1, sizeof(Person));
    if (*list == NULL)
    {
        return -1;
    }
    return 0;
}

Error fillList(Person **list, char *fileName)
{
    if (list == NULL)
    {
        return -1;
    }

    FILE *file = fopen(fileName, "r");
    if (file == NULL || feof(file))
    {
        return -2;
    }

    char name[size] = {0};
    char number[size] = {0};

    Person *previousElement = NULL;
    while (!feof(file))
    {
        fscanf(file, "%s", name);
        fscanf(file, "%s", number);
        Person *person = calloc(1, sizeof(Person));
        if (person == NULL)
        {
            fclose(file);
            return -3;
        }
        strcpy((*list)->name, name);
        strcpy((*list)->number, number);
        (*list)->next = previousElement;
        previousElement = (*list);
    }
    fclose(file);
    return 0;
}

void mergeSorting(Person *list)
{
}

// Error printList(Person *list)
// {
//     if (list == NULL)
//     {
//         return -1;
//     }

//     Node *currentElement = list->head;
//     while (currentElement != NULL)
//     {
//         printf("%s %s\n", currentElement->name, currentElement->number);
//         currentElement = currentElement->next;
//     }
//     return 0;
// }

// void freeList(Person *list)
// {
//     if (list == NULL)
//     {
//         return;
//     }

//     Node *currentElement = list->head;
//     Node *previousElement = currentElement;
//     while (currentElement != NULL)
//     {
//         currentElement = currentElement->next;
//         free(previousElement);
//         previousElement = NULL;
//         previousElement = currentElement;
//     }
//     free(list);
// }