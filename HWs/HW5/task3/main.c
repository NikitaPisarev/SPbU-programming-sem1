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
    int priorityCurrentCharacter = 0;
    int topElementStack = 0;
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

        priorityCurrentCharacter = priorities(input[i]);
        if (priorityCurrentCharacter == 5) // Extra character(s)
        {
            return -5;
            freeStack(stack);
        }

        if (priorityCurrentCharacter == 3) // Opening parenthesis
        {
            if ((errorCode = push(stack, input[i])) != 0)
            {
                freeStack(stack);
                return errorCode;
            }
        }

        if (priorityCurrentCharacter == 4) // Closing parenthesis
        {
            if (isEmpty(stack))
            {
                freeStack(stack);
                return -6;
            }
            pop(stack, &topElementStack);
            while (topElementStack != '(' )
            {
                if (isEmpty(stack))
                {
                    freeStack(stack);
                    return -7;
                }
                output[currentOutput++] = topElementStack;
                output[currentOutput++] = ' ';
                pop(stack, &topElementStack);
            }
        }

        if (priorityCurrentCharacter == 1 || priorityCurrentCharacter == 2) // Operations
        {
            if (isEmpty(stack))
            {
                push(stack, input[i]);
                continue;
            }
            top(stack, &topElementStack);
            while (priorities(topElementStack) <= priorityCurrentCharacter)
            {
                pop(stack, &topElementStack);
                output[currentOutput++] = topElementStack;
                output[currentOutput++] = ' ';
                if (isEmpty(stack))
                {
                    break;
                }
                top(stack, &topElementStack);
            }
            if ((errorCode = push(stack, input[i])) != 0)
            {
                freeStack(stack);
                return errorCode;
            }
        }
    }

    while (!isEmpty(stack)) // If there are still elements left in the stack, then we put them in the output
    {
        pop(stack, &topElementStack);
        if (priorities(topElementStack) == 3)
        {
            freeStack(stack);
            return -8;
        }
        output[currentOutput++] = topElementStack;
        output[currentOutput++] = ' ';
    }
    freeStack(stack);
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