#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
int evenNumbersAhead(int array[], int lengthArray)
{
    int counterPermutations = 0;
    for (int i = 0; i < lengthArray; ++i)
    {
        if (array[i] % 2 == 0)
        {
            continue;
        }

        int current = i + 1;
        while (current < lengthArray && array[current] % 2 != 0)
        {
            ++current;
        }

        if (current >= lengthArray)
        {
            break;
        }
        swap(&array[i], &array[current]);
        ++counterPermutations;
    }
    return counterPermutations;
}

bool test1()
{
    int array[5] = {1, 2, 3, 4, 5};
    int correctArray[5] = {2, 4, 3, 1, 5};
    evenNumbersAhead(array, 5);
    for (int i = 0; i < 5; ++i)
    {
        if (array[i] != correctArray[i])
        {
            return false;
        }
    }
    return true;
}

bool test2()
{
    int array[6] = {8, 2, 4, 6, 5, 1};
    int correctArray[6] = {8, 2, 4, 6, 5, 1};
    int counterPermutations = evenNumbersAhead(array, 6);
    for (int i = 0; i < 6; ++i)
    {
        if (array[i] != correctArray[i])
        {
            return false;
        }
    }
    return counterPermutations == 0;
}

bool tests()
{
    return test1() && test2();
}

int main()
{
    setlocale(LC_ALL, "RU-ru");

    if (!tests())
    {
        printf("Тесты провалены.\n");
        return 0;
    }

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

    evenNumbersAhead(array, lengthArray);
    printf("Преобразованный массив:\n");
    printArray(array, lengthArray);

    free(array);
    return 0;
}