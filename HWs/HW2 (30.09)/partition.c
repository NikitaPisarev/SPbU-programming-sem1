#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define arraySize 30
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

void partition(int array[], int index, int rigthElement)
{
    int leftElement = index + 1;

    for (int current = leftElement; current < rigthElement; ++current)
    {
        if (array[index] > array[current])
        {
            swap(&array[current], &array[leftElement]);
            ++leftElement;
        }
    }

    swap(&array[index], &array[leftElement - 1]);
}

void main()
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
}