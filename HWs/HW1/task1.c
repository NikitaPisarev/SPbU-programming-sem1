#include <stdio.h>


int main()
{
    float number = 0;
    float numberSquar = 0;
    float result = 0;
    int scan_res = 0;

    do
    {
        printf("Enter an argument: ");
        scan_res = scanf("%f", &number);

        if (!scan_res)
        {
            printf("Incorrect input. Try again!");
            scanf("%*[^\n]");
        }
    } while (!scan_res);


    numberSquar = number * number;
    result = numberSquar * (numberSquar + number) + numberSquar + number + 1.0;

    printf("Result for X^4 + X^3 + X^2 + X + 1 = %f\n", result);

    return 0;
}