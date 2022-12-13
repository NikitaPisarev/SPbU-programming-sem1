#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define arraySize 20
#define maximumNumber 150

void printArr(int array[])
{
    printf("[ ");
    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("]");
}

void swap(int *firstNumber, int *secondNumber)
{
    int temp = *firstNumber;
    *firstNumber = *secondNumber;
    *secondNumber = temp;
}

void partition(int array[], int leftIndex, int rigthIndex)
{
    int leftElement = leftIndex + 1;

    for (int current = leftElement; current < rigthIndex; ++current)
    {
        if (array[leftIndex] > array[current])
        {
            swap(&array[current], &array[leftElement]);
            ++leftElement;
        }
    }

    swap(&array[leftIndex], &array[leftElement - 1]);
}

int main()
{
    int array[arraySize] = { 0 };

    srand(time(0));

    for (int i = 0; i < arraySize; ++i)
    {
        array[i] = rand() % maximumNumber;
    }

    printf("The array was like this:\n");
    printArr(array);

    partition(array, 0, arraySize);

    printf("\nThe array has become like this:\n");
    printArr(array);
    return 0;
}