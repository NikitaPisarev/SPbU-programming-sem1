#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Stack/stack.h"

#define maximumExpression 256

int priorities(char symbol)
{
    if (symbol == '*' || symbol == '/')
    {
        return 1;
    }
    if (symbol == '+' || symbol == '-')
    {
        return 2;
    }
    if (symbol == '(')
    {
        return 3;
    }
    if (symbol == ')')
    {
        return 4;
    }
    return 5;
}

int infixToPostfix(char input[], char *output, int lengthInput)
{
    Stack *stack = createStack();
    if (stack == NULL)
    {
        printf("Stack creation error.\n");
        return -4;
    }

    int currentOutput = 0;
    int priority = 0;
    int topElement = 0;
    int errorCode = 0;
    for (int i = 0; i < lengthInput; ++i)
    {
        if (input[i] == ' ') // Spaces
        {
            continue;
        }

        if (input[i] - '0' >= 0 && input[i] - '0' <= 9) // Numbers
        {
            output[currentOutput++] = input[i];
            output[currentOutput++] = ' ';
            continue;
        }

        priority = priorities(input[i]);
        if (priority == 5) // Extra character(s)
        {
            return -5;
            freeStack(stack);
            free(stack);
        }

        if (priority == 3) // Opening parenthesis
        {
            if ((errorCode = push(stack, input[i])) != 0)
            {
                freeStack(stack);
                free(stack);
                return errorCode;
            }
        }

        if (priority == 4) // Closing parenthesis
        {
            if (isEmpty(stack))
            {
                freeStack(stack);
                free(stack);
                return -6;
            }
            pop(stack, &topElement);
            while (topElement != '(' )
            {
                if (isEmpty(stack))
                {
                    freeStack(stack);
                    free(stack);
                    return -7;
                }
                output[currentOutput++] = topElement;
                output[currentOutput++] = ' ';
                pop(stack, &topElement);
            }
        }

        if (priority == 1 || priority == 2) // Operations
        {
            if (isEmpty(stack))
            {
                push(stack, input[i]);
                continue;
            }
            top(stack, &topElement);
            while (priorities(topElement) <= priority)
            {
                pop(stack, &topElement);
                output[currentOutput++] = topElement;
                output[currentOutput++] = ' ';
                if (isEmpty(stack))
                {
                    break;
                }
                top(stack, &topElement);
            }
            if ((errorCode = push(stack, input[i])) != 0)
            {
                freeStack(stack);
                free(stack);
                return errorCode;
            }
        }
    }

    while (!isEmpty(stack))
    {
        pop(stack, &topElement);
        if (priorities(topElement) == 3)
        {
            freeStack(stack);
            free(stack);
            return -8;
        }
        output[currentOutput++] = topElement;
        output[currentOutput++] = ' ';
    }
    freeStack(stack);
    free(stack);
    return 0;
}

bool testInfixToPostfix()
{
    char inputTest1[] = "(1 + 1) * 2";
    char outputTest1[10] = { 0 };
    char correctOutput1[] = "1 1 + 2 *";
    if (infixToPostfix(inputTest1, outputTest1, 11) != 0)
    {
        printf("The infixToPostfix function failed with error.\n");
        return false;
    }
    for (int i = 0; i < 9; ++i)
    {
        if (outputTest1[i] != correctOutput1[i])
        {
            return false;
        }
    }

    char inputTest2[] = "1 + (2 * 5 + 3) / 7";
    char outputTest2[18] = { 0 };
    char correctOutput2[] = "1 2 5 * 3 + 7 / +";
    if (infixToPostfix(inputTest2, outputTest2, 19) != 0)
    {
        printf("The infixToPostfix function failed with error.\n");
        return false;
    }
    for (int i = 0; i < 17; ++i)
    {
        if (outputTest2[i] != correctOutput2[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    if (!testInfixToPostfix())
    {
        printf("Tests failed!\n");
        return 0;
    }

    char input[maximumExpression] = { 0 };
    char output[maximumExpression] = { 0 };
    printf("Enter the expression (no more than %d characters):\n", maximumExpression);
    gets(input);
    unsigned char lengthInput = strlen(input);
    if (lengthInput == 0)
    {
        printf("Input error.\n");
        return 0;
    }

    int errorCode = 0;
    if ((errorCode = infixToPostfix(input, output, lengthInput)) != 0)
    {
        printf("The infixToPostfix function failed with error %d.\n", errorCode);
        return 0;
    }
    printf("Your expression is in reverse Polish notation:\n");
    printf("%s", output);
    return 0;
}