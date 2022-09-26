#include <stdio.h>
#include <stdbool.h>

int main()
{
    int arrayLength = 0;
    int counterZero = 0;
    int current = 1;
    int scan_res = 0;
    bool flagNumber = true;

    do
    {
        flagNumber = true;

        printf("Enter the amount of elements in the array: ");
        scan_res = scanf("%d", &arrayLength);

        if (arrayLength < 1)
        {
            flagNumber = false;
        }

        if (!scan_res || !flagNumber)
        {
            printf("Incorrect input (the length must be at least 1). Try again!\n");
            scanf("%*[^\n]");
        }
    } while (!scan_res || !flagNumber);

    printf("Enter an array, exactly %d element(s):\n", arrayLength);

    for (int i = 0; i < arrayLength; ++i)
    {
        scanf("%d", &current);
        if (current == 0)
        {
            ++counterZero;
        }
    }

    printf("Number of zero elements: %d\n", counterZero);

    return 0;
}