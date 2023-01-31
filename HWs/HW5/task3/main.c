#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Stack/stack.h"

#define maximumExpression 256

void printError()
{
    printf("// Error codes:\n");
    printf("-1: Stack not created\n");
    printf("-2: Stack head is missing(or memory allocation error for head)\n");
    printf("-3: Memory allocation error\n");
    printf("-4: Incorrect sequence\n");
}

int getPriority(char symbol)
{
    if (symbol == '*' || symbol == '/')
    {
        return 1;
    }
    if (symbol == '+' || symbol == '-')
    {
        return 2;
    }
    return 3;
}

int infixToPostfix(char input[], char *output, int lengthInput)
{
    Stack *stack = createStack();
    if (stack == NULL)
    {
        printf("Stack creation error.\n");
        return -1;
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

        if (input[i] >= '0' && input[i] <= '9') // Numbers
        {
            output[currentOutput++] = input[i];
            output[currentOutput++] = ' ';
            continue;
        }

        if (input[i] == '(')
        {
            if ((errorCode = push(stack, input[i])) != 0)
            {
                freeStack(stack);
                return errorCode;
            }
            continue;
        }

        if (input[i] == ')')
        {
            if (isEmpty(stack))
            {
                freeStack(stack);
                return -4;
            }
            pop(stack, &topElementStack);
            while (topElementStack != '(')
            {
                if (isEmpty(stack))
                {
                    freeStack(stack);
                    return -4;
                }
                output[currentOutput++] = topElementStack;
                output[currentOutput++] = ' ';
                pop(stack, &topElementStack);
            }
            continue;
        }

        priorityCurrentCharacter = getPriority(input[i]);
        if (priorityCurrentCharacter == 3) // Extra character(s)
        {
            return -4;
            freeStack(stack);
        }

        if (priorityCurrentCharacter == 1 || priorityCurrentCharacter == 2) // Operations
        {
            if (isEmpty(stack))
            {
                push(stack, input[i]);
                continue;
            }
            top(stack, &topElementStack);
            while (getPriority(topElementStack) <= priorityCurrentCharacter)
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
        if (topElementStack == '(')
        {
            freeStack(stack);
            return -4;
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
    char outputTest1[10] = {0};
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
    char outputTest2[18] = {0};
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

    char inputTest3[] = "9 + 7 * 3 - 6 / 2";
    char outputTest3[16] = {0};
    char correctOutput3[] = "9 7 3 * + 6 2 / - ";
    if (infixToPostfix(inputTest3, outputTest3, 17) != 0)
    {
        printf("The infixToPostfix function failed with error.\n");
        return false;
    }
    for (int i = 0; i < 15; ++i)
    {
        if (outputTest3[i] != correctOutput3[i])
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
        return -1;
    }

    char input[maximumExpression] = {0};
    char output[maximumExpression] = {0};
    printf("Enter the expression (no more than %d characters):\n", maximumExpression);
    gets(input);
    unsigned char lengthInput = strlen(input);
    if (lengthInput == 0)
    {
        printf("Input error.\n");
        return -1;
    }

    int errorCode = 0;
    if ((errorCode = infixToPostfix(input, output, lengthInput)) != 0)
    {
        printf("The infixToPostfix function failed with error %d.\n", errorCode);
        printError();
        return -1;
    }
    printf("Your expression is in reverse Polish notation:\n");
    printf("%s", output);
    return 0;
}