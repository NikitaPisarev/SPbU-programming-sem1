#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "qsort.h"

#define maximumSize 256

int mostCommonInSortedArray(int array[], int length, int *counterMaximum)
{
    int counter = 1;
    int mostCommon = array[0];
    *counterMaximum = 1;

    for (int i = 1; i < length; ++i)
    {
        if (array[i] == array[i - 1])
        {
            ++counter;
        }
        else
        {
            if (counter > *counterMaximum)
            {
                mostCommon = array[i - 1];
                *counterMaximum = counter;
            }

            counter = 1;
        }
    }

    if (counter > *counterMaximum) // If the most common number is at the end, then we never check the last element for the maximum
    {
        mostCommon = array[length - 2];
        *counterMaximum = counter;
    }
    return mostCommon;
}

bool testMostCommon()
{
    int array[5] = {0, 1, 1, 1, 0};
    int counterMaximum = 1;
    int mostCommonNumber = mostCommonInSortedArray(array, 5, &counterMaximum);

    return mostCommonNumber == 1 && counterMaximum == 3;
}

int main()
{
    int errorCode = testQuickSort();
    if (errorCode != 0)
    {
        printf("Tests failed! Error code %d.\n", errorCode);
        return 0;
    }

    if (!testMostCommon())
    {
        printf("MostCommon function tests failed!\n");
        return 0;
    }

    FILE *file = fopen("../HWs/HW4/task2/array.txt", "r");
    if (file == NULL)
    {
        printf("File opening error :(\n");
        return 0;
    }

    int arraySize = 0;
    char temp[maximumSize] = {0};

    while (fscanf(file, "%s", &temp) == 1)
    {
        ++arraySize;
    }

    if (arraySize == 0)
    {
        printf("File is empty.\n");
        return 0;
    }

    fseek(file, 0, SEEK_SET);
    int *array = calloc(arraySize, sizeof(int));
    if (array == NULL)
    {
        printf("Memory allocation error :(\n");
        return 0;
    }

    int scanResult = 0;
    for (int i = 0; i < arraySize; ++i)
    {
        scanResult = fscanf(file, "%d", &array[i]);
        if (scanResult == 0)
        {
            printf("Incorrect file structure.\n");
            fclose(file);
            free(array);
            return -1;
        }
    }
    fclose(file);

    quickSort(array, 0, arraySize - 1);
    int counterMaximum = 1;
    int mostCommonNumber = mostCommonInSortedArray(array, arraySize, &counterMaximum);

    if (counterMaximum == 1)
    {
        printf("All elements occur once.");
    }
    else
    {
        printf("The most common element is \"%d\", which has been encountered %d time(s).\n", mostCommonNumber, counterMaximum);
    }

    free(array);
    return 0;
}