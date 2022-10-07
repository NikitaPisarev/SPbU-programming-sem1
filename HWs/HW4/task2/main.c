#include <stdio.h>
#include <stdbool.h>
#include "qsort.h"

#define arraySizeBound 999

bool binarySearch(int array[], int firstIndex, int secondIndex, int key)
{
    int middle = (firstIndex + secondIndex) / 2;
    
    if (array[middle] == key)
    {
        return true;
    }

    if (firstIndex >= secondIndex)
    {
        return false;
    }   

    if (array[middle] < key)
    {
        binarySearch(array, middle + 1, secondIndex, key);
    }
    else
    {
        binarySearch(array, firstIndex, middle - 1, key);
    }
}

void main()
{
    int array[arraySizeBound] = { 0 };
    int arraySize = 0;
    int scan_res = 0;
    bool flagInput = true;

    do
    {
        printf("Enter size array: ");
        scan_res = scanf("%d", &arraySize);

        flagInput = true;

        if (!scan_res || arraySize < 1 || arraySize > arraySizeBound)
        {
            printf("Incorrect input (The size is positive and no more than %d). Try again!\n", arraySizeBound);
            scanf_s("%*[^\n]");

            flagInput = false;
        }
    } while (!scan_res || !flagInput);
    

    printf("Enter a array:\n");
    for (int i = 0; i < arraySize; ++i)
    {
        do
        {
            scan_res = scanf("%d", &array[i]);

            if (!scan_res)
            {
                printf("Incorrect input. Try again!\n");
                scanf_s("%*[^\n]");
            }
        } while (!scan_res);
    }

    quickSort(array, 0, arraySize - 1);

    int mostCommon = array[0];
    int counter = 1;
    int counterMaximum = 1;

    for (int i = 1; i < arraySize; ++i)
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
        mostCommon = array[arraySize - 2]; 
        counterMaximum = counter;
    }

    if (counterMaximum == 1)
    {
        printf("All elements occur once.");
    }
    else
    {
        printf("The most common element is %d, it has been encountered %d times.", mostCommon, counterMaximum);
    }
}