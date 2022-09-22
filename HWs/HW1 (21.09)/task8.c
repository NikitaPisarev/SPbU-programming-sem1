#include <stdio.h>
#include <stdbool.h>

void task8(void)
{
    int arrayLength = 0;
    int counterZero = 0;
    int sub = 1;
    int scan_res = 0;
    bool flagNumber = true;

    do
    {
        flagNumber = true;

        printf("\nEnter the amount of elements in the array: ");
        scan_res = scanf_s("%d", &arrayLength);

        if (arrayLength < 1)
        {
            flagNumber = false;
        }

        if (!scan_res || !flagNumber)
        {
            printf("Incorrect input (the length must be at least 1). Try again!");
            scanf_s("%*[^\n]");
        }
    } while (!scan_res || !flagNumber);

    printf("Enter an array, exactly %d element(s):\n", arrayLength);

    for (int i = 0; i < arrayLength; ++i)
    {
        scanf_s("%d", &sub);
        if (sub == 0)
        {
            ++counterZero;
        }
    }

    printf("Number of zero elements: %d\n\n", counterZero);
}