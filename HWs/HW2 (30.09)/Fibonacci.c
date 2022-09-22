#include <stdio.h>
#include <stdbool.h>

#define bound 47

int iteratFibonacci(int number)
{
    int firstNumber = 0;
    int secondNumber = 1;
    int counter = 0;
    int temp = 0;

    while (counter < number)
    {
        temp = secondNumber;
        secondNumber = secondNumber + firstNumber;
        firstNumber = temp;

        ++counter;
    }

    return firstNumber;
}

int recursFibonacci(int number)
{
    if (number == 0 || number == 1)
    {
        return number;
    }

    return recursFibonacci(number - 1) + recursFibonacci(number - 2);
}

void main()
{
    int number = 0;
    int scan_res = 0;
    bool flagNumber = true;

    do
    {
        flagNumber = true;

        printf("Enter which Fibonacci number you want to output: ");
        scan_res = scanf("%d", &number);

        if (number < 0 || number >= bound)
        {
            flagNumber = false;
        }

        if (!scan_res || !flagNumber)
        {
            printf("Incorrect input (the number must be non-negative and less than %d). Try again!\n", bound);
            scanf("%*[^\n]");
        }
    } while (!scan_res || !flagNumber);

    printf("The Fibonacci number of %d is %d\n", number, iteratFibonacci(number));
    printf("And also the %d Fibonacci number is %d", number + 1, recursFibonacci(number + 1));
}