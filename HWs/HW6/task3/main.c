#include <stdio.h>
#include "mergeSortList.h"

void printError()
{
    printf("Error codes:\n");
    printf("-1: File opening error\n");
    printf("-2: Memory allocation error\n");
}

int main()
{
    List *list = NULL;
    int errorCode = 0;
    if ((errorCode = fillList(&list, "../HWs/HW6/task3/data.txt")) != 0)
    {
        printf("The fillList function failed with error %d.\n", errorCode);
        printError();
        return 0;
    }

    int key = 0;
    printf("Hi, enter the sorting method (>= 0 - by name, < 0 - by number): ");
    scanf("%d", &key);
    mergeSorting(&list, key);
    printf("Phonebook:\n");
    printList(list);
    freeList(&list);
    return 0;
}