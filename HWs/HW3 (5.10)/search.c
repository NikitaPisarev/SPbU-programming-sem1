#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define arraySize 999
#define maximumNumber 100

void printArr(int array[], int lengthArray)
{
    printf("[ ");
    for (int i = 0; i < lengthArray; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("]");
}

void arrayRandom(int array[], int length)
{
    for (int i = 0; i < length; ++i)
    {
        array[i] = rand() % maximumNumber;
    }
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
    int lengthN = 0;
    int lengthK = 0;
    int scan_resN = 0;
    int scan_resK = 0;
    bool flagInput = true;

    do
    {
        printf("Enter \"N\" and \"K\": ");
        scan_resN = scanf("%d", &lengthN);
        scan_resK= scanf("%d", &lengthK);

        flagInput = true;

        if (!scan_resN || !scan_resK || lengthK <= 0 || lengthN <= 0)
        {
            printf("Incorrect input (\"N\" and \"K\" are positive and less than %d). Try again!\n", arraySize);
            scanf_s("%*[^\n]");

            flagInput = false;
        }
    } while (!scan_resN || !scan_resK);

    int arrayN[arraySize] = { 0 };
    int arrayK[arraySize] = { 0 };

    arrayRandom(arrayK, lengthK);
    arrayRandom(arrayN, lengthN);

    printf("\nThe array \"N\" looks like this:\n");
    printArr(arrayN, lengthN);
    printf("\nThe array \"K\" looks like this:\n");
    printArr(arrayK, lengthK);
    printf("\n\n");

    quickSort(arrayN, 0, lengthN - 1);
    
    for (int i = 0; i < lengthK; ++i)
    {
        if (binarySearch(arrayN, 0, lengthN - 1, arrayK[i]))
        {
            printf("\"%d\" is present in the array \"N\".\n", arrayK[i]);
        }
        else
        {
            printf("\"%d\" is missing in the array \"N\".\n", arrayK[i]);
        }
    }
}