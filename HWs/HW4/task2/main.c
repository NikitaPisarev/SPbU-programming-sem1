#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "qsort.h"

void mostCommon(int array[], int length)
{
    int mostCommon = array[0];
    int counter = 1;
    int counterMaximum = 1;

    for (int i = 1; i < length; ++i)
    {
        if (array[i] == array[i - 1])
        {
            ++counter;
        }
        else 
        {
            if (counter > counterMaximum)
            {
                mostCommon = array[i - 1];
                counterMaximum = counter;
            }

            counter = 1;
        }
    }

    if (counter > counterMaximum)  // If the most common number is at the end, then we never check the last element for the maximum
    {
        mostCommon = array[length - 2]; 
        counterMaximum = counter;
    }

    if (counterMaximum == 1)
    {
        printf("All elements occur once.\n");
    }
    else
    {
        printf("The most common element is %d, it has been encountered %d times.\n", mostCommon, counterMaximum);
    }
}

int main()
{
    FILE *file = fopen("array.txt", "r");

    if (file == NULL)
    {
        printf("File opening error :(\n");
        return 0;
    }

    int arraySize = 0;
    int temp = 0;

    while (fscanf(file, "%d", &temp) == 1)
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

    for (int i = 0; i < arraySize; ++i)
    {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);

    quickSort(array, 0, arraySize - 1);
    mostCommon(array, arraySize);

    free(array);

    return 0;
}