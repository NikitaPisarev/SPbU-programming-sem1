#include <stdio.h>
#include <stdbool.h>

#define arraySizeBound 999

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

void mostCommon(int array[], int length, int *mostCommon, int *counterMaximum)
{
    int counter = 1;

    for (int i = 1; i < length; ++i)
    {
        if (array[i] == array[i - 1])
        {
            ++counter;
        }
        else 
        {
            if (counter > *counterMaximum)
            {
                *mostCommon = array[i - 1];
                *counterMaximum = counter;
            }

            counter = 1;
        }
    }

    if (counter > *counterMaximum)  // If the most common number is at the end, then we never check the last element for the maximum
    {
        *mostCommon = array[length - 2]; 
        *counterMaximum = counter;
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

bool testMostCommon()
{
    int array[5] = {0, 1, 1, 1, 0};
    int counterMaximum = 1;
    int mostCommonNumber = array[0];
    mostCommon(array, 5, &mostCommonNumber, &counterMaximum);

    return mostCommonNumber == 1 && counterMaximum == 3;
}

int main()
{
    int errorCode = testQuickSort();
    if (errorCode != 0)
    {
        printf("QuickSort function tests failed! Error code %d.\n", errorCode);
        return 0;
    }

    if (!testMostCommon())
    {
        printf("MostCommon function tests failed!\n");
        return 0;
    }

    int array[arraySizeBound] = { 0 };
    int arraySize = 0;
    int scan_res = 0;
    bool isCorrectInput = true;

    do
    {
        printf("Enter size array: ");
        scan_res = scanf("%d", &arraySize);

        isCorrectInput = true;

        if (!scan_res || arraySize < 1 || arraySize > arraySizeBound)
        {
            printf("Incorrect input (The size is positive and no more than %d). Try again!\n", arraySizeBound);
            scanf_s("%*[^\n]");

            isCorrectInput = false;
        }
    } while (!scan_res || !isCorrectInput);
    

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

    int counterMaximum = 1;
    int mostCommonNumber = array[0];
    mostCommon(array, arraySize, &mostCommonNumber, &counterMaximum);

    if (counterMaximum == 1)
    {
        printf("All elements occur once.");
    }
    else
    {
        printf("The most common element is \"%d\", which has been encountered %d time(s).\n", mostCommonNumber, counterMaximum);
    }

    return 0;
}