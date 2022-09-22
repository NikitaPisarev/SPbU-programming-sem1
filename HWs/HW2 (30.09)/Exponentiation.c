#include <stdio.h>
#include <math.h>

double power(int number, int degree)
{
    int result = 1;

    for (int i = 1; i <= abs(degree); ++i)
    {
        result = result * number;
    }

    if (degree > 0)
    {
        return result;  
    }
    else
    {
        return 1.0 / result;
    }
}

double binaryPower(int number, int degree)
{
    int result = 1;
    int absDegree = abs(degree);

    while (absDegree > 0)
    {
        if (absDegree % 2 == 1)
        {
            result = result * number;
            --absDegree;
        }

        number = number * number;
        absDegree /= 2;
    }

    if (degree > 0)
    {
        return result;
    }
    else
    {
        return 1.0 / result;
    }
}

void main()
{
    int number = 0;
    int degree = 0;
    int scan_resNumber = 0;
    int scan_resDegree = 0;

    do
    {
        printf("Enter the number and degree: ");
        scan_resNumber = scanf("%d", &number);
        scan_resDegree= scanf("%d", &degree);

        if (!scan_resNumber || !scan_resDegree)
        {
            printf("Incorrect input. Try again!\n");
            scanf_s("%*[^\n]");
        }
    } while (!scan_resNumber || !scan_resDegree);

    if (number == 0 && degree == 0)
    {
        printf("Uncertainty");
    }
    else
    {
        printf("Binary search: ");
        if (degree >= 0)
        {
            printf("%d^%d is %.0lf\n", number, degree, binaryPower(number, degree));

        }
        else
        {
            printf("%d^(%d) is %.15lf\n", number, degree, binaryPower(number, degree));
        }

        printf("Linear search: ");
        if (degree >= 0)
        {
            printf("%d^%d is %.0lf\n", number, degree, power(number, degree));

        }
        else
        {
            printf("%d^(%d) is %.15lf\n", number, degree, power(number, degree));
        }
    }
}