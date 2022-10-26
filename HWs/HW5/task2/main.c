#include <stdio.h>
#include <stdlib.h>
#include "../Stack/stack.h"

int main()
{
    Stack *stack = createStack();

    if (stack == NULL)
    {
        printf("Stack creation error.\n");
        return 0;
    }
    
    printf("Enter the bracket sequence:\n");

    unsigned char currentСharacter = 0;
    int topElement = 0;

    while ((currentСharacter = getc(stdin)) != '\n')
    {
        if (currentСharacter == '(' || currentСharacter == '[' || currentСharacter == '{')
        {
            push(stack, currentСharacter);
            continue;
        }

        if (currentСharacter == ')')
        {
            top(stack, &topElement);

            if (topElement != (currentСharacter - 1)) // In the encoding, the numbers of brackets () differ by one
            {
                printf("No.\n");
                return 0;
            }
            pop(stack, &topElement);

            continue;
        }

        if (currentСharacter == ']' || currentСharacter == '}')
        {
            top(stack, &topElement);

            if (topElement != (currentСharacter - 2)) // In the encoding, the numbers of brackets {} and [] differ by two
            {
                printf("No.\n");
                return 0;
            }
            pop(stack, &topElement);

            continue;
        }

        printf("No the bracket sequence\n");
        return 0;
    }

    if (!isEmpty(stack))
    {
        printf("No.\n");
        freeStack(stack);
        free(stack);
        return 0;
    }

    freeStack(stack);
    free(stack);

    printf("Yes");
    return 0;
}