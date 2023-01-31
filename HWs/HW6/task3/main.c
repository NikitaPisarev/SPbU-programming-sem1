#include <stdio.h>
#include "mergeSortList.h"

#define maximumSize 256

void printError()
{
    printf("Error codes:\n");
    printf("-1: File opening error\n");
    printf("-2: Memory allocation error\n");
}

Error fillList(List **list, char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL || feof(file))
    {
        return -1;
    }

    char name[maximumSize] = {0};
    char number[maximumSize] = {0};
    int errorCode = 0;
    while (!feof(file))
    {
        fscanf(file, "%s", name);
        fscanf(file, "%s", number);
        if ((errorCode = addElement(list, name, number)) != 0)
        {
            return errorCode;
        }
    }

    fclose(file);
    return 0;
}

int main()
{
    if (!tests())
    {
        printf("Tests failed.\n");
        return -1;
    }

    List *list = NULL;
    int errorCode = 0;
    if ((errorCode = fillList(&list, "../HWs/HW6/task3/data.txt")) != 0)
    {
        printf("The fillList function failed with error %d.\n", errorCode);
        printError();
        return -1;
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