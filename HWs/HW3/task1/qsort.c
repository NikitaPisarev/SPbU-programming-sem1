#include <stdio.h>
#include <stdbool.h>
#include "../quickSort.h"

#define arraySizeBound 1000

void printArray(int array[], int lengthArray)
{
    printf("[ ");
    for (int i = 0; i < lengthArray; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("]");
}

int main()
{
    int errorCode = testQuickSort();
    if (errorCode != 0)
    {
        printf("Tests failed! Error code %d.\n", errorCode);
        return 0;
    }

    int array[arraySizeBound] = {0};
    int arraySize = 0;
    int scanResult = 0;
    bool isCorrectInput = true;

    do
    {
        printf("Enter size array: ");
        scanResult = scanf("%d", &arraySize);

        isCorrectInput = true;

        if (!scanResult || arraySize < 1 || arraySize > arraySizeBound)
        {
            printf("Incorrect input (The size is positive and no more than %d). Try again!\n", arraySizeBound);
            scanf_s("%*[^\n]");

            isCorrectInput = false;
        }
    } while (!isCorrectInput);

    printf("Enter an array:\n");
    for (int i = 0; i < arraySize; ++i)
    {
        do
        {
            scanResult = scanf("%d", &array[i]);

            if (!scanResult)
            {
                printf("Incorrect input. Try again!\n");
                scanf_s("%*[^\n]");
            }
        } while (!scanResult);
    }

    quickSort(array, 0, arraySize - 1);
    printf("Sorted array:\n");
    printArray(array, arraySize);

    return 0;
}
