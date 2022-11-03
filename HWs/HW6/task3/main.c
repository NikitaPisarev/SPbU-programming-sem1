#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mergeSortList.h"

int main()
{
    List *list = NULL;
    int errorCode = 0;
    if ((errorCode = fillList(&list, "data.txt")) != 0)
    {
        printf("The fillList function failed with error %d.\n", errorCode);
        return 0;
    }

    int key = 0;
    printf("Hi, enter the sorting method ( >= 0 - by name, < 0 - by number): ");
    scanf("%d", &key);
    mergeSorting(&list, key);
    printf("Phonebook:\n");
    printList(list);
    freeList(&list);
    return 0;
}