#include <stdio.h>
#include <math.h>

int main()
{
    int dividend = 0;
    int divider = 0;
    int quotient = 0;

    printf("Enter a dividend and divider separated by a space: ");
    scanf("%d%d", &dividend, &divider);

    if (divider == 0)
    {
        printf("Divider can't be zero.\n");
        return 0;
    }

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

    printf("The quotient %d by %d is %d.", dividend, divider, quotient);
    
    return 0;
}