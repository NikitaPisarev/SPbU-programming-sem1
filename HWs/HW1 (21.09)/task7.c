#include <stdio.h>
#include <stdbool.h>

#define arraySize 9999

void task7(void)
{
    int upPrime = 0;
    bool primers[arraySize] = { false };

    int scan_res = 0;
    bool flagNumber = true;

    do
    {
        flagNumber = true;

        printf("\nEnter the number to which you want to output prime numbers: ");
        scan_res = scanf_s("%d", &upPrime);

        if (upPrime <= 2 || upPrime >= 10000)
        {
            flagNumber = false;
        }

        if (!scan_res || !flagNumber)
        {
            printf("Incorrect input (number must be greater than 2 and less than 10000). Try again! ");
            scanf_s("%*[^\n]");
        }
    } while (!scan_res || !flagNumber);

    //Решето Эратосфена
    for (int i = 2; i * i < upPrime; ++i)
    {
        if (!primers[i])
        {
            for (int j = i * 2; j < upPrime; j += i)
            {
                primers[j] = true;
            }
        }
    }

    printf("Prime numbers: ");

    for (int i = 2; i < upPrime; ++i)
    {
        if (!primers[i])
        {
            printf("%d ", i);
        }
    }
    printf("\n\n");
}