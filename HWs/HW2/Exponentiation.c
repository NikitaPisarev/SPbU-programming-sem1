#include <stdio.h>
#include <math.h>

double power(int number, int degree)
{
    int result = 1;

    for (int i = 1; i <= abs(degree); ++i)
    {
        result = result * number;
    }

    return (degree > 0) ? result : 1.0 / result;
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

    return (degree > 0) ? result : 1.0 / result;
}

int main()
{
    int number = 0;
    int degree = 0;
    int scanResNumber = 0;
    int scanResDegree = 0;

    do
    {
        printf("Enter the number and degree: ");
        scanResNumber = scanf("%d", &number);
        scanResDegree = scanf("%d", &degree);

        if (!scanResNumber || !scanResDegree)
        {
            printf("Incorrect input. Try again!\n");
            scanf_s("%*[^\n]");
        }
    } while (!scanResNumber || !scanResDegree);

    if (number == 0 && degree == 0)
    {
        printf("Uncertainty.\n");
        return 0;
    }
    
    if (degree >= 0)
    {
        printf("Binary exponentiation ");
        printf("%d^%d is %.0lf\n", number, degree, binaryPower(number, degree));
        printf("Linear exponentiation ");
        printf("%d^%d is %.0lf\n", number, degree, power(number, degree));
    }
    else
    {
        printf("Binary exponentiation ");
        printf("%d^(%d) is %.15lf\n", number, degree, binaryPower(number, degree));
        printf("Linear exponentiation ");
        printf("%d^(%d) is %.15lf\n", number, degree, power(number, degree));
    }

    return 0;
}