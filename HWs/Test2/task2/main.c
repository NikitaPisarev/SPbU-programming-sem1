#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

int main()
{
    Stack *stack = createStack();
    if (stack == NULL)
    {
        printf("Memory allocation error.\n");
        return 0;
    }

    int action = -1;
    bool isContinue = true;
    int value = 0;
    int errorCode = 0;
    while (isContinue)
    {
        printf("Enter a number from 0-4: ");
        scanf("%d", &action);

        switch (action)
        {
        case 0:
            printf("Good luck!\n");
            isContinue = false;
            break;

        case 1:
            printf("Enter the value: ");
            scanf("%d", &value);
            errorCode = push(stack, value);
            if (errorCode != 0)
            {
                printf("The push function finished with error %d.\n", errorCode);
                isContinue = false;
            }
            break;

        case 2:
            errorCode = pop(stack, &value);
            if (errorCode != 0)
            {
                printf("The pop function finished with error %d.\n", errorCode);
                isContinue = false;
            }
            printf("The value that was on the stack: %d\n", value);
            break;

        case 3:
            errorCode = add(stack);
            if (errorCode != 0)
            {
                printf("The add function finished with error %d.\n", errorCode);
                isContinue = false;
            }
            break;

        case 4:
            printf("Stack: ");
            printStack(stack);
            break;

        default:
            printf("There is no such command :(\n");
            break;
        }
    }

    freeStack(stack);
    return 0;
}