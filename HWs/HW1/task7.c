#include <stdio.h>
#include <stdbool.h>

#define arraySize 9999

void task7(void)
{
    int upperPrimeNumber = 0;
    bool primers[arraySize] = { false };

    int scan_res = 0;
    bool flagNumber = true;

    do
    {
        flagNumber = true;

        printf("\nEnter the number up to which you want to see prime numbers: ");
        scan_res = scanf_s("%d", &upperPrimeNumber);

        if (!scan_res || upperPrimeNumber <= 2 || upperPrimeNumber >= 10000)
        {
            printf("Incorrect input (number must be greater than 2 and no more than %d). Try again! ", arraySize);
            scanf_s("%*[^\n]");
            flagNumber = false;
        }
    } while (!scan_res || !flagNumber);

    //Решето Эратосфена
    for (int i = 2; i * i <= upperPrimeNumber; ++i)
    {
        if (!primers[i])
        {
            for (int j = i * 2; j <= upperPrimeNumber; j += i)
            {
                primers[j] = true;
            }
        }
    }

    printf("Prime numbers: ");

    for (int i = 2; i <= upperPrimeNumber; ++i)
    {
        if (!primers[i])
        {
            printf("%d ", i);
        }
    }
    printf("\n\n");
}