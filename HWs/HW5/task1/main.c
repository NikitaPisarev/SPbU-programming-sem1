#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../Stack/stack.h"

void printError()
{
    printf("// Error codes:\n");
    printf("-1: Stack not created\n");
    printf("-2: Stack head is missing(or memory allocation error for head)\n");
    printf("-3: Memory allocation error\n");
}

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

int postfixNotationCalculation(char string[], int lengthString, int *result)
{
    Stack *stack = createStack();
    if (stack == NULL)
    {
        printf("Stack creation error.\n");
        return -1;
    }

    int errorCode = 0;
    for (int i = 0; i < lengthString; ++i)
    {
        if (string[i] == ' ')
        {
            continue;
        }

        if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/')
        {
            if ((errorCode = operations(stack, string[i])) != 0)
            {
                if (errorCode == -4)
                {
                    printf("This is not reverse Polish notation.\n");
                }
                else
                {
                    printf("The operations function failed with error %d.\n", errorCode);
                    printError();
                }
                freeStack(stack);
                return -1;
            }

            continue;
        }

        if (string[i] < '0' || string[i] > '9')
        {
            printf("Reading error, enter only \"+, -, *, /\" and digits 0-9.\n");
            freeStack(stack);
            return -1;
        }

        if ((errorCode = push(stack, (int)(string[i] - '0'))) != 0)
        {
            printf("The push function failed with error %d.\n", errorCode);
            printError();
            freeStack(stack);
            return -1;
        }
    }

    if ((errorCode = pop(stack, result)) != 0)
    {
        printf("The pop function failed with error %d.\n", errorCode);
        printError();
        freeStack(stack);
        return -1;
    }

    if (!isEmpty(stack))
    {
        printf("Incorrect input.\n");
        freeStack(stack);
        return -1;
    }

    freeStack(stack);
    return 0;
}

bool testOperations()
{
    char testEntry[] = "9 6 - 1 2 + *";
    int resultTest = 0;
    int errorCode = postfixNotationCalculation(testEntry, 13, &resultTest);
    if (errorCode != 0)
    {
        return false;
    }
    return resultTest == 9;
}

int main()
{
    if (!testOperations())
    {
        printf("Tests failed!\n");
        return -1;
    }

    int lengthString = 0;
    printf("Enter the size of the Polish record: ");
    scanf("%d", &lengthString);
    if (lengthString <= 0)
    {
        printf("Incorrect record size.\n");
        return -1;
    }
    char *string = calloc(lengthString + 1, sizeof(char));
    if (string == NULL)
    {
        printf("Memory allocation error.\n");
        return -1;
    }
    printf("Enter the expression in reverse Polish notation:\n");
    getchar();
    fgets(string, lengthString + 1, stdin);

    int result = 0;
    int errorCode = postfixNotationCalculation(string, lengthString, &result);
    if (errorCode != 0)
    {
        return -1;
    }

    printf("Answer: %d", result);
    free(string);
    return 0;
}