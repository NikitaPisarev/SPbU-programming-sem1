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
        for (int j = 0; j < lengthArray - (i + 1); ++j)
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

    int lengthAuxiliaryArray = maximumElement - minimumElement + 1;
    int *arrayAuxiliary = calloc(lengthAuxiliaryArray, sizeof(int));
    if (arrayAuxiliary == NULL)
    {
        return -1;
    }

    for (int i = 0; i < lengthArray; ++i)
    {
        ++arrayAuxiliary[array[i] - minimumElement];
    }

    int currentPosition = 0;

    for (int i = 0; i < lengthAuxiliaryArray; ++i)
    {
        for (int j = 0; j < arrayAuxiliary[i]; ++j)
        {
            array[currentPosition++] = i + minimumElement;
        }
    }

    free(arrayAuxiliary);

    return 0;
}

int main()
{
    int array[arraySizeBound] = { 0 };
    int arraySize = 0;
    int scanRes = 0;
    bool isCorrectInput = true; 

    do
    {
        printf("Enter size array: ");
        scanRes = scanf("%d", &arraySize);

        isCorrectInput = true;

        if (!scanRes || arraySize < 1 || arraySize > arraySizeBound)
        {
            printf("Incorrect input (The size is positive and no more than %d). Try again!\n", arraySizeBound);
            scanf_s("%*[^\n]");

            isCorrectInput = false;
        }
    } while (!isCorrectInput);
    

    printf("Enter an array:\n");
    for (int i = 0; i < arraySize; ++i)
    {
        do
        {
            scanRes = scanf("%d", &array[i]);

            if (!scanRes)
            {
                printf("Incorrect input. Try again!\n");
                scanf_s("%*[^\n]");
            }
        } while (!scanRes);
    }

    char typeSort = 0;
    bool isCorrectInputChar = true;

    printf("Choose the type of sorting by Bubble or Counting (B/C)?\n");
    do
    {
        isCorrectInputChar = true;

        getchar();
        scanRes = scanf("%c", &typeSort);

        if (!scanRes || (typeSort != 'B' && typeSort != 'C'))
        {
            printf("Incorrect input (Only \"B\" or \"C\"). Try again!\n");
            scanf_s("%*[^\n]");

            isCorrectInputChar = false;
        }
    } while (!isCorrectInputChar);

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

    return 0;
}