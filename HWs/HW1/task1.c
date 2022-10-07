#include <stdio.h>

void task1(void)
{
    float number = 0;
    float numberSquar = 0;
    float result = 0;
    int scan_res = 0;

    do
    {
        printf("\nEnter an argument: ");
        scan_res = scanf_s("%f", &number);

        if (!scan_res)
        {
            printf("Incorrect input. Try again! ");
            scanf_s("%*[^\n]");
        }
    } while (!scan_res);


    numberSquar = number * number;
    result = numberSquar * (numberSquar + number) + numberSquar + number + 1.0;

    printf("Result for X^4 + X^3 + X^2 + X + 1 = %f\n\n", result);
}