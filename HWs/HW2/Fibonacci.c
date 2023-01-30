#include <stdio.h>
#include <stdbool.h>

#define bound 47

int iterativeFibonacci(unsigned int number)
{
    int previousNumber = 0;
    int currentNumber = 1;

    for (int i = 0; i < number; ++i)
    {
        currentNumber = currentNumber + previousNumber;
        previousNumber = currentNumber - previousNumber;
    }

    return previousNumber;
}

int recursiveFibonacci(unsigned int number)
{
    if (number == 0 || number == 1)
    {
        return number;
    }

    return recursiveFibonacci(number - 1) + recursiveFibonacci(number - 2);
}

void main()
{
    unsigned int number = 0;
    int scan_res = 0;
    bool isIncorrectInput = true;

    do
    {
        isIncorrectInput = true;

        printf("Enter which Fibonacci number you want to output: ");
        scan_res = scanf("%d", &number);

        if (!scan_res || !isIncorrectInput || number < 0 || number >= bound)
        {
            printf("Incorrect input (the number must be non-negative and less than %d). Try again!\n", bound);
            scanf("%*[^\n]");

            isIncorrectInput = false;
        }
    } while (!scan_res || !isIncorrectInput);

    printf("The Fibonacci number of %d is %d\n", number, iterativeFibonacci(number));
    printf("And also the %d Fibonacci number is %d\n", number + 1, recursiveFibonacci(number + 1));
}