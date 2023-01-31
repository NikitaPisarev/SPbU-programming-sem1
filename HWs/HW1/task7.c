#include <stdio.h>
#include <stdbool.h>

#define arraySize 9999

int main()
{
    int upperPrimeNumber = 0;
    bool primers[arraySize] = { false };

    int scan_res = 0;
    bool flagNumber = true;

    do
    {
        flagNumber = true;

        printf("Enter the number up to which you want to see prime numbers: ");
        scan_res = scanf("%d", &upperPrimeNumber);

        if (!scan_res || upperPrimeNumber <= 1 || upperPrimeNumber >= 10000)
        {
            printf("Invalid input (the number must be at least 2 and no more than %d). Try again!\n", arraySize);
            scanf("%*[^\n]");
            flagNumber = false;
        }
    } while (!scan_res || !flagNumber);

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

    printf("Prime number(s): ");

    for (int i = 2; i <= upperPrimeNumber; ++i)
    {
        if (!primers[i])
        {
            printf("%d ", i);
        }
    }
    return 0;
}