#include <stdio.h>
#include <stdbool.h>

#define arraySizeBound 100
#define maximumValues 9999

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

void countingSort(int array[], int lengthArray)
{
    int arrayAux[maximumValues] = { 0 };

    for (int i = 0; i < lengthArray; ++i)
    {
        ++arrayAux[array[i]];
    }

    int temp = 0;

    for (int i = 0; i < maximumValues; ++i)
    {
        for (int j = 0; j < arrayAux[i]; ++j)
        {
            array[temp++] = i;
        }
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

    (typeSort == 'B') ? bubbleSort(array, arraySize) : countingSort(array, arraySize);
    
    printf("Sorted array:\n");
    printArr(array, arraySize);
}