#include <stdio.h>
#include <stdlib.h>
#include "mergeSortList.h"

int main()
{
    Person *list = NULL;
    if (listCreate(&list) == -1)
    {
        printf("Memory allocation error.\n");
        return 0;
    }

    int errorCode = 0;
    if ((errorCode = fillList(&list, "data.txt")) != 0)
    {
        printf("The fillList function failed with error %d.\n", errorCode);
        return 0;
    }

    printf("List:\n");
    printList(&list);
    return 0;
}