#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

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

void swap(int *firstNumber, int *secondNumber)
{
    int temp = *firstNumber;
    *firstNumber = *secondNumber;
    *secondNumber = temp;
}

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

bool binarySearch(int array[], int leftIndex, int rightIndex, int key)
{
    int middle = (leftIndex + rightIndex) / 2;
    
    if (array[middle] == key)
    {
        return true;
    }

    if (leftIndex >= rightIndex)
    {
        return false;
    }   

    if (array[middle] < key)
    {
        binarySearch(array, middle + 1, rightIndex, key);
    }
    else
    {
        binarySearch(array, leftIndex, middle - 1, key);
    }
}

bool testQuickSort1()
{
    int array[5] = {5, 4, 3, 2, 1};

    quickSort(array, 0, 4);

    for (int i = 0; i < 5; ++i)
    {
        if (array[i] != i + 1)
        {
            return false;
        }
    }

    return true;
}

bool testQuickSort2()
{
    int array[4] = {-3, 0, -1, -2};
    int correctArray[4] = {-3, -2, -1, 0};

    quickSort(array, 0, 3);

    for (int i = 0; i < 4; ++i)
    {
        if (array[i] != correctArray[i])
        {
            return false;
        }
    }

    return true;
}

bool testQuickSort3()
{
    int array[6] = {2, 2, 2, 2, 2, 2};

    quickSort(array, 0, 5);

    for (int i = 0; i < 6; ++i)
    {
        if (array[i] != 2)
        {
            return false;
        }
    }

    return true;
}

int testQuickSort()
{
    if (!testQuickSort1())
    {
        return -1;
    }
    
    if (!testQuickSort2())
    {
        return -2;
    }

    if (!testQuickSort3())
    {
        return -3;
    }

    return 0;   
}

bool testBinarySearch1()
{
    int array[5] = {1, 2, 3, 4, 5};
    return binarySearch(array, 0, 4, 4);
}

bool testBinarySearch2()
{
    int array[5] = {5, 4, 3, 2, 1};
    quickSort(array, 0, 4);
    return binarySearch(array, 0, 4, 2);
}

bool testBinarySearch3()
{
    int array[6] = {15, 4, -3, 0, 11};
    quickSort(array, 0, 5);
    return !binarySearch(array, 0, 5, 2);
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
    int scan_resN = 0;
    int scan_resK = 0;
    bool isCorrectInput = true;

    do
    {
        printf("Enter the length of the array \"N\" then the array \"K\": ");
        scan_resN = scanf("%d", &lengthArrayN);
        scan_resK= scanf("%d", &lengthArrayK);

        isCorrectInput = true;

        if (!scan_resN || !scan_resK || lengthArrayK <= 0 || lengthArrayN <= 0)
        {
            printf("Incorrect input (\"N\" and \"K\" are positive and less than %d). Try again!\n", arraySize);
            scanf_s("%*[^\n]");

            isCorrectInput = false;
        }
    } while (!scan_resN || !scan_resK);

    int arrayN[arraySize] = { 0 };
    int arrayK[arraySize] = { 0 };

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
        if (binarySearch(arrayN, 0, lengthArrayN - 1, arrayK[i]))
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