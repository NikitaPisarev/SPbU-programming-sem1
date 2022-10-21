#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define arraySizeBound 100

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

void bubbleSort(int array[], int lengthArray)
{
    for (int i = 0; i < lengthArray - 1; ++i)
    {
        for (int j = 0; j < lengthArray - 1; ++j)
        {
            if (array[j] > array[j + 1])
            {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}

int countingSort(int array[], int lengthArray)
{
    int maximumElement = array[0];
    int minimumElement = array[0];

    for (int i = 1; i < lengthArray; ++i)
    {
        if (array[i] > maximumElement)
        {
            maximumElement = array[i];
        }

        if (array[i] < minimumElement)
        {
            minimumElement = array[i];
        }
    }

    int *arrayAux = calloc(maximumElement - minimumElement + 1, sizeof(int));

    if (arrayAux == NULL)
    {
        return -1;
    }

    for (int i = 0; i < lengthArray; ++i)
    {
        ++arrayAux[array[i] - minimumElement];
    }

    int temp = 0;

    for (int i = 0; i < (maximumElement - minimumElement + 1); ++i)
    {
        for (int j = 0; j < arrayAux[i]; ++j)
        {
            array[temp++] = i + minimumElement;
        }
    }

    free(arrayAux);

    return 0;
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

    char typeSort = '\0';
    bool flagInputChar = true;

    printf("Choose the type of sorting by Bubble or Counting (B/C)?\n");
    do
    {
        flagInputChar = true;

        getchar();
        scan_res = scanf("%c", &typeSort);

        if (!scan_res || (typeSort != 'B' && typeSort != 'C'))
        {
            printf("Incorrect input (Only \"B\" or \"C\"). Try again!\n");
            scanf_s("%*[^\n]");

            flagInputChar = false;
        }
    } while (!scan_res || !flagInputChar);

    if (typeSort == 'B') 
    {
        bubbleSort(array, arraySize);

        printf("Sorted array:\n");
        printArr(array, arraySize);
    } 
    else if (countingSort(array, arraySize) == 0)
    {
        printf("Sorted array:\n");
        printArr(array, arraySize);
    }
    else
    {
        printf("Error :(\n");
    }
}