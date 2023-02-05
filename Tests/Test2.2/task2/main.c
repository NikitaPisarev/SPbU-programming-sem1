#include <stdio.h>
#include "set.h"

void printError(void)
{
    printf(" -1: Set not created\n");
    printf(" -2: Memory allocation error\n");
}

int main()
{
    Set *firstSet = setCreate();
    if (firstSet == NULL)
    {
        printf("Memory allocation error.\n");
        return -1;
    }
    Set *secondSet = setCreate();
    if (secondSet == NULL)
    {
        printf("Memory allocation error.\n");
        freeSet(firstSet);
        return -1;
    }
    int lengthFirstSet = 0;
    int lengthSecondSet = 0;
    int value = 0;
    int errorCode = 0;
    printf("Enter the number of elements you want to add to the first set: ");
    scanf("%d", &lengthFirstSet);
    if (lengthFirstSet < 0)
    {
        printf("Incorrect set length.\n");
        freeSet(firstSet);
        freeSet(secondSet);
        return -1;
    }
    if (lengthFirstSet != 0)
    {
        printf("Enter the elements of the first set:\n");
    }
    for (int i = 0; i < lengthFirstSet; ++i)
    {
        scanf("%d", &value);
        if ((errorCode = addElement(firstSet, value)) != 0)
        {
            printf("\"addElement\" function ended with error %d.\n", errorCode);
            printError();
            freeSet(firstSet);
            freeSet(secondSet);
            return -1;
        }
    }
    printf("Enter the number of elements you want to add to the second set: ");
    scanf("%d", &lengthSecondSet);
    if (lengthSecondSet < 0)
    {
        printf("Incorrect set length.\n");
        freeSet(firstSet);
        freeSet(secondSet);
        return -1;
    }
    if (lengthSecondSet != 0)
    {
        printf("Enter the elements of the second set:\n");
    }
    for (int i = 0; i < lengthSecondSet; ++i)
    {
        scanf("%d", &value);
        if ((errorCode = addElement(secondSet, value)) != 0)
        {
            printf("\"addElement\" function ended with error %d.\n", errorCode);
            printError();
            freeSet(firstSet);
            freeSet(secondSet);
            return -1;
        }
    }
    printf("\nYour sets:\n");
    printSet(firstSet);
    printSet(secondSet);
    Set *unionSet = setCreate();
    if (unionSet == NULL)
    {
        printf("Memory allocation error.");
        freeSet(firstSet);
        freeSet(secondSet);
        return -1;
    }
    if ((errorCode = setUnion(firstSet, secondSet, unionSet)) != 0)
    {
        printf("\"setUnion\" function ended with error %d.\n", errorCode);
        printError();
        freeSet(firstSet);
        freeSet(secondSet);
        freeSet(unionSet);
        return -1;
    }
    printf("\nUnion of sets:\n");
    printSet(unionSet);
    freeSet(firstSet);
    freeSet(secondSet);
    freeSet(unionSet);
    return 0;
}