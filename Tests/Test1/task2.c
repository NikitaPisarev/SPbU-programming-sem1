#include <stdio.h>
#include <stdbool.h>

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

void sortShell(int array[], int length)
{
    if (length > 8)
    {
        for (int k = 8; k > 0; k /= 2)
        {
            for (int i = 0; i < length - k; ++i)
            {
                int j = i + k;

                while (j > 0 && array[j - k] > array[j])
                {
                    swap(&array[j - k], &array[j]);
                    j = j - k;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < length - 1; ++i)
        {
            int j = i + 1;

            while (j > 0 && array[j - 1] > array[j])
            {
                swap(&array[j - 1], &array[j]);
                --j;
            }
        }     
    }
}

int main()
{
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

    sortShell(array, sizeArray);

    printf("Отсортированный масссив:");
    printArray(array, sizeArray);
}