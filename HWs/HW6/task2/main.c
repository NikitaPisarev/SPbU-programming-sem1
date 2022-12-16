#include <stdio.h>
#include "circularList.h"

void printError()
{
    printf("Error codes:\n");
    printf("-1: List not created\n");
    printf("-2: Memory allocation error\n");
}

int survivor(int numberOfWarriors, int step)
{
    List *list = listCreate();
    if (list == NULL)
    {
        return -3;
    }

    int errorCode = 0;
    for (int i = 0; i < numberOfWarriors; ++i)
    {
        if ((errorCode = push(list, i)) != 0)
        {
            freeList(list);
            return errorCode;
        }
    }

    int killingPosition = step - 1;
    int survivor = 0;
    while (!isOneElementLeft(list))
    {
        if ((errorCode = pop(list, killingPosition, &survivor)) != 0)
        {
            freeList(list);
            return errorCode;
        }
        --numberOfWarriors;
        killingPosition = (killingPosition + step - 1) % numberOfWarriors;
    }

    if ((errorCode = pop(list, 0, &survivor)) != 0)
    {
        freeList(list);
        return errorCode;
    }
    freeList(list);
    return survivor;
}

bool testSurvivor()
{
    return survivor(2, 8) == 0 && survivor(10, 3) == 3 && survivor(5, 5) == 1 && survivor(6784, 67) == 6731;
}

int main()
{
    if (!testSurvivor())
    {
        printf("Tests failed!\n");
        return 0;
    }

    int numberOfWarriors = 0;
    int step = 0;
    printf("Enter the number of warriors and the killing step:\n");
    scanf("%d", &numberOfWarriors);
    scanf("%d", &step);
    if (numberOfWarriors <= 0 || step <= 0)
    {
        printf("Invalid value.\n");
        return 0;
    }

    int numberSurvivor = 0;
    if ((numberSurvivor = survivor(numberOfWarriors, step)) >= 0)
    {
        printf("The survivor: %d", numberSurvivor);
    }
    else
    {
        printf("The program finished with error %d.\n", numberSurvivor);
        printError();
    }
    return 0;
}