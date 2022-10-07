#include <stdio.h>
#include <math.h>

void task2(void)
{
    int dividend = 0;
    int divider = 0;
    int quotient = 0;

    printf("\nEnter a dividend and divider separated by a space: ");
    scanf_s("%d%d", &dividend, &divider);

    if (divider == 0)
    {
        printf("Divider can't be zero.\n\n");
    }
    else
    {
        int absDividend = abs(dividend);
        int absB = abs(divider);


        while (absDividend >= absB)
        {
            absDividend -= absB;
            ++quotient;
        }

        if (dividend < 0 && absDividend != 0)
        {
            ++quotient;
        }

        if ((dividend < 0 && divider > 0) || (dividend > 0 && divider < 0))
        {
            quotient = -quotient;
        }

        printf("The quotient %d by %d is %d.\n\n", dividend, divider, quotient);
    }
}