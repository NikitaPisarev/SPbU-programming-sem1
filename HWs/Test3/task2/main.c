#include <stdio.h>
#include "mergeSortingList.h"

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
    int amount = 0;
    char currentCharacter = 0;
    int counter = 1;
    int errorCode = 0;
    name[0] = '\n'; // Preservation of the invariant "Name starts with '\n'"
    while (!feof(file))
    {
        while ((currentCharacter = getc(file)) != '-')
        {
            name[counter] = currentCharacter;
            ++counter;
        }
        name[counter] = '\0';
        fscanf(file, "%d", &amount);
        if ((errorCode = addElement(list, name, amount)) != 0)
        {
            return errorCode;
        }

        for (int i = 0; i < counter; ++i)
        {
            name[i] = 0;
        }
        counter = 0;
    }

    fclose(file);
    return 0;
}

int main()
{
    List *list = NULL;
    int errorCode = fillList(&list, "../HWs/Test3/task2/storage.txt");
    if (errorCode != 0)
    {
        printf("The fillList function failed with error %d.\n", errorCode);
        printError();
        return -1;
    }
    int n = 0;
    printf("Enter the number \"N\": ");
    scanf("%d", &n);
    if (n < 0)
    {
        printf("Incorrect meaning.\n");
        return -1;
    }
    int m = 0;
    printf("Enter the number \"M\": ");
    scanf("%d", &m);
    if (m < 0)
    {
        printf("Incorrect meaning.\n");
        return -1;
    }
    if (n != 0)
    {
        printf("PRODUCTS WITH 50 PER CENT DISCOUNT:");
        findingAndPrintingtheFirstDiscount(&list, n);
        printf("\n\n");
    }
    if (list != NULL && m != 0)
    {
        printf("Products with a 25 percent discount:");
        findingAndPrintingtheSecondDiscount(&list, m);
        printf("\n\n");
    }
    if (list != NULL)
    {
        printf("Products without discount:");
        printList(list);
    }
    freeList(&list);
    return 0;
}