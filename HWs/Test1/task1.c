#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#define maxSizeArray 100

void printArray(int array[], int length)
{
    printf("\n[ ");
    for (int i = 0; i < length; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("]\n");
}

void swap(int *firstNumber, int *secondNumber)
{
    int temp = *firstNumber;
    *firstNumber = *secondNumber;
    *secondNumber = temp;
}

void insertsSort(int array[], int length)
{
    for (int i = 1; i < length; ++i)
    {
        if (array[i] % 2 == 0)
        {
            int current = i;
            int j = 1;

            while (current - j >= 0)
            {
                if ((array[current - j] % 2 == 0) && array[current - j] > array[current])
                {
                    swap(&array[current - j], &array[current]);
                    current -= j;
                    j = 0;
                }
                ++j;
            }
        }
    }
}

bool test(int arrayMain[], int arrayRes[], int length)
{
    insertsSort(arrayMain, length);

    for (int i = 0; i < length; ++i)
    {
        if (arrayMain[i] != arrayRes[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "RU-ru");

    int arrayTest[5] = {6 , 4, 3, 2, 1};
    int arrayAnswer[5] = {2, 4, 3, 6, 1};

    if (!test(arrayTest, arrayAnswer, 5))
    {
        printf("Тест провален :(");
        return 0;
    }

    int array[maxSizeArray] = { 0 };
    int sizeArray = 0;

    printf("Привет, введи размер массива: ");
    int scan_resSize = 0;
    bool flagInput = true;
    do
    {
        scan_resSize = scanf("%d", &sizeArray);
        flagInput = true;

        if (!scan_resSize || sizeArray <= 0)
        {
            printf("Неккоретный ввод, попробуй еще раз! (Размер больше 0 и не более чем %d)\n", maxSizeArray);
            scanf("%*[^\n]");
            flagInput = false;
        }
    } while (!scan_resSize || !flagInput);
    
    printf("Введи элементы массива (не больше чем %d):\n", sizeArray);
    int scan_resElement = 0;
    for (int i = 0; i < sizeArray; ++i)
    {
        do
        {
            scan_resElement = scanf("%d", &array[i]);

            if (!scan_resElement)
            {
                printf("Неккоретный ввод, попробуй еще раз!\n");
                scanf("%*[^\n]");
            }
        } while (!scan_resElement);
    }

    insertsSort(array, sizeArray);

    printf("\nОтсортированные четные числа:");
    printArray(array, sizeArray);

    return 0;
}