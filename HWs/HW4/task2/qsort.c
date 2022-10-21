#include "qsort.h"

// swaps objects firstNumber and secondNumber
void swap(int *firstNumber, int *secondNumber)
{
    int temp = *firstNumber;
    *firstNumber = *secondNumber;
    *secondNumber = temp;
}

// rearranges the elements in the segment [leftIndex, rightIndex]
// so that all the elements to the left of "rightIndex" are smaller
// and to the right are larger and returns the index of "rightIndex"
int partition(int array[], int leftIndex, int rightIndex)
{
    for (int current = leftIndex; current < rightIndex; ++current)
    {
        if (array[rightIndex] > array[current])
        {
            swap(&array[current], &array[leftIndex]);
            ++leftIndex;
        }
    }

    swap(&array[rightIndex], &array[leftIndex]);

    return leftIndex;
}

// sorts by inserting a segment [leftIndex, rightIndex] in an array
void insertsSort(int array[], int leftIndex, int rightIndex)
{
    for (int i = leftIndex; i < rightIndex; ++i)
    {
        int j = i + 1;

        while (j > leftIndex && array[j - 1] > array[j])
        {
            swap(&array[j - 1], &array[j]);
            --j;
        }
    }
}

// quick sorting of a segment [leftIndex, rightIndex] in an array
void quickSort(int array[], int leftIndex, int rightIndex)
{
    if (rightIndex - leftIndex <= 8)
    {
        insertsSort(array, leftIndex, rightIndex);
    }
    else
    {
        int reference = partition(array, leftIndex, rightIndex);
        quickSort(array, leftIndex, reference - 1);
        quickSort(array, reference + 1, rightIndex);
    }  
}
