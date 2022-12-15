#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Stack/stack.h"

int checkBalanced(char sequence[], int lengthSequence)
{
    Stack *stack = createStack();
    if (stack == NULL)
    {
        printf("Stack creation error.\n");
        return -4;
    }

    int errorCode = 0;
    int topElement = 0;
    for (int i = 0; i < lengthSequence; ++i)
    {
        if (sequence[i] == '(' || sequence[i] == '[' || sequence[i] == '{')
        {
            if ((errorCode = push(stack, sequence[i])) != 0)
            {
                freeStack(stack);
                return errorCode;
            }
            continue;
        }

        if (sequence[i] == ')')
        {
            if ((errorCode = pop(stack, &topElement)) != 0 ||
                (topElement != (sequence[i] - 1))) // In the encoding, the numbers of brackets () differ by one
            {
                freeStack(stack);
                return 0;
            }

            continue;
        }

        if (sequence[i] == ']' || sequence[i] == '}')
        {
            if ((errorCode = pop(stack, &topElement)) != 0 ||
                (topElement != (sequence[i] - 2))) // In the encoding, the numbers of brackets {} and [] differ by two
            {
                freeStack(stack);
                return 0;
            }
        }
    }

    if (!isEmpty(stack))
    {
        freeStack(stack);
        return 0;
    }
    return 1;
}

bool testCheckBalanced()
{
    char sequence1[7] = "({[]})";
    if (!checkBalanced(sequence1, 7))
    {
        return false;
    }

    char sequence2[5] = "([})";
    if (checkBalanced(sequence2, 5))
    {
        return false;
    }

    char sequence3[6] = "([a])";
    if (!checkBalanced(sequence3, 5))
    {
        return false;
    }

    char sequence4[1] = "";
    if (!checkBalanced(sequence4, 1))
    {
        return false;
    }
    return true;
}

int main()
{
    if (!testCheckBalanced())
    {
        printf("Tests failed!\n");
        return 0;
    }

    int lengthSequence = 0;
    printf("Enter the length of the bracket sequence: ");
    scanf("%d", &lengthSequence);
    if (lengthSequence <= 0)
    {
        printf("Invalid length value.\n");
        return 0;
    }
    printf("Enter the bracket sequence:\n");
    char *sequence = calloc(lengthSequence, sizeof(char));
    if (sequence == NULL)
    {
        printf("Memory allocation error.\n");
        return 0;
    }
    scanf("%s", sequence);

    int errorCode = checkBalanced(sequence, lengthSequence);
    if (errorCode == 1)
    {
        printf("Good bracket sequence!\n");
    }
    else if (errorCode == 0)
    {
        printf("Bad bracket sequence.\n");
    }
    else
    {
        printf("The program terminated with error code %d.\n", errorCode);
    }
    return 0;
}