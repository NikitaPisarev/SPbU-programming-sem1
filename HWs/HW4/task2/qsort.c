#include "qsort.h"

// swaps objects firstNumber and secondNumber
void swap(int *firstNumber, int *secondNumber)
{
    int temp = *firstNumber;
    *firstNumber = *secondNumber;
    *secondNumber = temp;
}

// rearranges the elements in the segment [firstIndex, secondIndex]
// so that all the elements to the left of "secondIndex" are smaller
// and to the right are larger and returns the index of "secondIndex"
int partition(int array[], int firstIndex, int secondIndex)
{
    for (int current = firstIndex; current < secondIndex; ++current)
    {
        if (array[secondIndex] > array[current])
        {
            swap(&array[current], &array[firstIndex]);
            ++firstIndex;
        }
    }

    swap(&array[secondIndex], &array[firstIndex]);

    return firstIndex;
}

// sorts by inserting a segment [firstIndex, secondIndex] in an array
void insertsSort(int array[], int firstIndex, int secondIndex)
{
    for (int i = firstIndex; i < secondIndex; ++i)
    {
        int j = i + 1;

        while (j > firstIndex && array[j - 1] > array[j])
        {
            swap(&array[j - 1], &array[j]);
            --j;
        }
    }
}

// quick sorting of a segment [firstIndex, secondIndex] in an array
void quickSort(int array[], int firstIndex, int secondIndex)
{
    if (secondIndex - firstIndex <= 8)
    {
        insertsSort(array, firstIndex, secondIndex);
    }
    else
    {
        int reference = partition(array, firstIndex, secondIndex);
        quickSort(array, firstIndex, reference - 1);
        quickSort(array, reference + 1, secondIndex);
    }  
}
