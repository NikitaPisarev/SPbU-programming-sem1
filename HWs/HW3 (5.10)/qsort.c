#include <stdio.h>
#include <stdbool.h>

#define arraySizeBound 1000


void printArr(int array[], int lengthArray)
{
    printf("[ ");
    for (int i = 0; i < lengthArray; ++i)
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
    printf("Sorted array:\n");
    printArr(array, arraySize);
}
