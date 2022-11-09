#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

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

bool isCorrect(int array[], int lengthArray)
{
    for (int i = 0; i < lengthArray - 1; ++i)
    {
        if (array[i] > array[i + 1])
        {
            return false;
        }
    }

    return true;
}

void shuffle(int array[], int lengthArray)
{
    for (int i = 0; i < lengthArray; ++i)
    {
        swap(&array[i], &array[rand() % lengthArray]);
    }
}

void bogoSorting(int array[], int lengthArray)
{
    while (!isCorrect(array, lengthArray))
    {
        shuffle(array, lengthArray);
    }
}

int main()
{
    setlocale(LC_ALL, "RU-ru");

    printf("Введи размер массива: ");
    int lengthArray = 0;
    scanf("%d", &lengthArray);
    if (lengthArray <= 0)
    {
        printf("Недопустимое значение длины массива.\n");
        return 0;
    }

    int *array = calloc(lengthArray, sizeof(int));
    if (array == NULL)
    {
        printf("Ошибка выделения памяти.\n");
        return 0;
    }

    printf("Введи массив:\n");
    for (int i = 0; i < lengthArray; ++i)
    {
        scanf("%d", &array[i]);
    }

    srand(time(0));
    bogoSorting(array, lengthArray);
    printf("Отсортированный массив:\n");
    printArray(array, lengthArray);

    free(array);
    return 0;
}