#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

void selectionSort(int array[], int lengthArray)
{
    for (int i = 0; i < lengthArray; ++i)
    {
        int indexMinimum = i;

        for (int j = i + 1; j < lengthArray; ++j)
        {
            if (array[j] < array[indexMinimum])
            {
                indexMinimum = j;
            }
        }

        swap(&array[i], &array[indexMinimum]);
    }
}

int main()
{
    setlocale(LC_ALL, "RU-ru");

    int lengthArray = 0;

    printf("Привет, введи размер массива: ");
    scanf("%d", &lengthArray);

    if (lengthArray <= 0)
    {
        printf("Недопустимое значение размера массива.\n");
        return 0;
    }

    int *array = (int *) calloc(lengthArray, sizeof(int));

    printf("Введи массив:\n");
    for (int i = 0; i < lengthArray; ++i)
    {
        scanf("%d", &array[i]);
    }

    selectionSort(array, lengthArray);

    printf("Отсортированный массив:\n");
    printArr(array, lengthArray);

    return 0;
}