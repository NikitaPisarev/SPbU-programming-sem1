#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "../quickSort.h"

#define arraySize 999
#define maximumNumber 100

void printArray(int array[], int lengthArray)
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

bool binarySearchInSortedArray(int array[], int leftIndex, int rightIndex, int key)
{
    if (leftIndex > rightIndex)
    {
        return false;
    }

    int middle = (leftIndex + rightIndex) / 2;
    if (array[middle] == key)
    {
        return true;
    }

    if (array[middle] < key)
    {
        binarySearchInSortedArray(array, middle + 1, rightIndex, key);
    }
    else
    {
        binarySearchInSortedArray(array, leftIndex, middle - 1, key);
    }
}

bool testBinarySearch1()
{
    int array[5] = {1, 2, 3, 4, 5};
    return binarySearchInSortedArray(array, 0, 4, 4);
}

bool testBinarySearch2()
{
    int array[5] = {5, 4, 3, 2, 1};
    quickSort(array, 0, 4);
    return binarySearchInSortedArray(array, 0, 4, 2);
}

bool testBinarySearch3()
{
    int array[6] = {15, 4, -3, 0, 11};
    quickSort(array, 0, 5);
    return !binarySearchInSortedArray(array, 0, 5, 2);
}

int testBinarySearch()
{
    if (!testBinarySearch1())
    {
        return -1;
    }

    if (!testBinarySearch2())
    {
        return -2;
    }

    if (!testBinarySearch3())
    {
        return -3;
    }

    return 0;
}

int main()
{
    int errorCode = testQuickSort();
    if (errorCode != 0)
    {
        printf("QuickSort function tests failed! Error code %d.\n", errorCode);
        return 0;
    }

    errorCode = testBinarySearch();
    if (errorCode != 0)
    {
        printf("BinarySearch function tests failed! Error code %d.\n", errorCode);
        return 0;
    }

    int lengthArrayN = 0;
    int lengthArrayK = 0;
    int scanResultN = 0;
    int scanResultK = 0;
    bool isCorrectInput = true;

    do
    {
        printf("Enter the length of the array \"N\" then the array \"K\": ");
        scanResultN = scanf("%d", &lengthArrayN);
        scanResultK = scanf("%d", &lengthArrayK);

        isCorrectInput = true;

        if (!scanResultN || !scanResultK || lengthArrayK <= 0 ||
            lengthArrayN <= 0 || lengthArrayK > arraySize ||
            lengthArrayN > arraySize)
        {
            printf("Incorrect input (\"N\" and \"K\" are positive and less than %d). Try again!\n", arraySize + 1);
            scanf_s("%*[^\n]");

            isCorrectInput = false;
        }
    } while (!isCorrectInput);

    int arrayN[arraySize] = {0};
    int arrayK[arraySize] = {0};

    srand(time(0));
    arrayRandom(arrayK, lengthArrayK);
    arrayRandom(arrayN, lengthArrayN);

    printf("\nThe array \"N\" looks like this:\n");
    printArray(arrayN, lengthArrayN);
    printf("\nThe array \"K\" looks like this:\n");
    printArray(arrayK, lengthArrayK);
    printf("\n\n");

    quickSort(arrayN, 0, lengthArrayN - 1);

    for (int i = 0; i < lengthArrayK; ++i)
    {
        if (binarySearchInSortedArray(arrayN, 0, lengthArrayN - 1, arrayK[i]))
        {
            printf("\"%d\" is present in the array \"N\".\n", arrayK[i]);
        }
        else
        {
            printf("\"%d\" is missing in the array \"N\".\n", arrayK[i]);
        }
    }

    return 0;
}