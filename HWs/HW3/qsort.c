#include <stdio.h>
#include <stdbool.h>

#define arraySizeBound 1000
#define sizeInsertionSort 10

void printArray(int array[], int lengthArray)
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

int partition(int array[], int leftIndex, int rigthIndex)
{
    for (int current = leftIndex; current < rigthIndex; ++current)
    {
        if (array[rigthIndex] > array[current])
        {
            swap(&array[current], &array[leftIndex]);
            ++leftIndex;
        }
    }

    swap(&array[rigthIndex], &array[leftIndex]);

    return leftIndex;
}

void insertsSort(int array[], int leftIndex, int rigthIndex)
{
    for (int i = leftIndex; i < rigthIndex; ++i)
    {
        int j = i + 1;

        while (j > leftIndex && array[j - 1] > array[j])
        {
            swap(&array[j - 1], &array[j]);
            --j;
        }
    }
}

void quickSort(int array[], int leftIndex, int rigthIndex)
{
    if (rigthIndex - leftIndex <= sizeInsertionSort - 2)
    {
        insertsSort(array, leftIndex, rigthIndex);
    }
    else
    {
        int reference = partition(array, leftIndex, rigthIndex);
        quickSort(array, leftIndex, reference - 1);
        quickSort(array, reference + 1, rigthIndex);
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

    quickSort(array, 0, 3);

    int correctArray[4] = {-3, -2, -1, 0};

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

int main()
{
    int errorCode = testQuickSort();
    if (errorCode != 0)
    {
        printf("Tests failed! Error code %d.\n", errorCode);
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
    printf("Sorted array:\n");
    printArray(array, arraySize);

    return 0;
}
