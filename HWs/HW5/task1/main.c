#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Stack/stack.h"

int operations(Stack *stack, unsigned char sign)
{
    int errorCode = 0;

    if (isEmpty(stack))
    {
        return -4;
    }

    int firstValue = 0;
    if ((errorCode = pop(stack, &firstValue)) != 0)
    {
        return errorCode;
    }

    if (isEmpty(stack))
    {
        return -4;
    }

    int secondValue = 0;
    if ((errorCode = pop(stack, &secondValue)) != 0)
    {
        return errorCode;
    }

    switch (sign)
    {
    case '+':
        if ((errorCode = push(stack, firstValue + secondValue)) != 0)
        {
            return errorCode;
        }

        break;

    case '-':
        if ((errorCode = push(stack, secondValue - firstValue)) != 0)
        {
            return errorCode;
        }

        break;

    case '*':
        if ((errorCode = push(stack, firstValue * secondValue)) != 0)
        {
            return errorCode;
        }

        break;

    case '/':
        if ((errorCode = push(stack, secondValue / firstValue)) != 0)
        {
            return errorCode;
        }

        break;
    }

    return 0;
}

bool testOperations()
{
    char testEntry[] = "9 6 - 1 2 + *";

    Stack *stack = createStack();
    if (stack == NULL)
    {
        printf("Stack creation error.\n");
        return false;
    }

    for (int i = 0; i < 13; ++i)
    {
        unsigned char currentСharacter = testEntry[i];

        if (currentСharacter == ' ')
        {
            continue;
        }

        if (currentСharacter == '+' || currentСharacter == '-' || currentСharacter == '*' || currentСharacter == '/')
        {
            if (operations(stack, currentСharacter) != 0)
            {
                printf("Error in operations function.\n");
                freeStack(stack);
                return false;
            }

            continue;
        }

        if (push(stack, (int)currentСharacter - (int)'0') != 0)
        {
            printf("Error in push function.\n");
            freeStack(stack);
            return false;
        }
    }

    int resultTest = 0;
    if (pop(stack, &resultTest) != 0)
    {
        printf("Error in pop function.\n");
        freeStack(stack);
        return false;
    }

    freeStack(stack);
    return resultTest == 9;
}

int main()
{
    if (!testOperations())
    {
        printf("Tests failed!\n");
        return 0;
    }

    printf("Enter the expression in reverse Polish notation:\n");

    Stack *stack = createStack();
    if (stack == NULL)
    {
        printf("Stack creation error.\n");
        return 0;
    }

    unsigned char currentСharacter = 0;
    int errorCode = 0;

    while ((currentСharacter = getc(stdin)) != '\n')
    {
        if (currentСharacter == ' ')
        {
            continue;
        }

        if (currentСharacter == '+' || currentСharacter == '-' || currentСharacter == '*' || currentСharacter == '/')
        {
            if ((errorCode = operations(stack, currentСharacter)) != 0)
            {
                if (errorCode == -4)
                {
                    printf("This is not reverse Polish notation.\n");
                }
                else
                {
                    printf("The operations function failed with error %d.\n", errorCode);
                }
                freeStack(stack);
                return 0;
            }

            continue;
        }

        if (currentСharacter < '0' || currentСharacter > '9')
        {
            printf("Reading error, enter only \"+, -, *, /\" and digits 0-9.\n");
            freeStack(stack);
            return 0;
        }

        if ((errorCode = push(stack, (int)(currentСharacter - '0'))) != 0)
        {
            printf("The push function failed with error %d.\n", errorCode);
            freeStack(stack);
            return 0;
        }
    }

    int result = 0;
    if ((errorCode = pop(stack, &result)) != 0)
    {
        printf("The pop function failed with error %d.\n", errorCode);
        freeStack(stack);
        return 0;
    }

    if (isEmpty(stack))
    {
        printf("");
        freeStack(stack);
        return -1;
    }

    freeStack(stack);
    printf("Answer: %d", result);
    return 0;
}