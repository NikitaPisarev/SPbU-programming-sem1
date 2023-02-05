#include <stdio.h>
#include <stdbool.h>
#include "list.h"

void printError()
{
    printf(" -1: List not created\n");
    printf(" -2: Memory allocation error\n");
    printf(" -3: No such index found\n");
}

void printActions()
{
    printf(" ----------------------------------------------------\n");
    printf(" 0 - Exit\n");
    printf(" 1 - Add number to sortable list\n");
    printf(" 2 - Remove item from list by index\n");
    printf(" 3 - Extract two numbers from a list,\n");
    printf("     add them up and put the sum into a sortable list\n");
    printf(" 4 - Print list\n");
    printf(" 5 - View the list of commands\n");
    printf(" ----------------------------------------------------\n");
}

int main()
{
    List *list = listCreate();
    if (list == NULL)
    {
        printf("List creation error.\n");
        return 0;
    }

    int action = -1;
    bool isContinue = true;
    int value = 0;
    int index = 0;
    int errorCode = 0;

    printf("Hi this is a sortable list, here is what i can:\n");
    printActions();
    while (isContinue)
    {
        printf("Enter a number from 0-5: ");
        scanf("%d", &action);

        switch (action)
        {
        case 0:
            printf("Good luck!\n");
            isContinue = false;
            break;

        case 1:
            printf("Enter a number: ");
            scanf("%d", &value);
            errorCode = addElement(list, value);
            if (errorCode != 0)
            {
                printf("ERROR! code: %d\n", errorCode);
                printError();
                isContinue = false;
            }
            else
            {
                printf("Completed!\n");
            }
            break;

        case 2:
            printf("Enter index: ");
            scanf("%d", &index);
            errorCode = deleteElement(list, index, &value);
            if (errorCode != 0)
            {
                printf("ERROR! code: %d\n", errorCode);
                printError();
                isContinue = false;
            }
            else
            {
                printf("Completed! Item %d removed.\n", value);
            }
            break;

        case 3:
            int index2 = 0;
            int value2 = 0;
            printf("Enter indices (for example: 10 22): ");
            scanf("%d", &index);
            scanf("%d", &index2);

            errorCode = deleteElement(list, index, &value);
            if (errorCode != 0)
            {
                printf("ERROR! code: %d\n", errorCode);
                printError();
                isContinue = false;
                break;
            }
            errorCode = deleteElement(list, index, &value2);
            if (errorCode != 0)
            {
                printf("ERROR! code: %d\n", errorCode);
                printError();
                isContinue = false;
                break;
            }

            errorCode = addElement(list, value + value2);
            if (errorCode != 0)
            {
                printf("ERROR! code: %d\n", errorCode);
                printError();
                isContinue = false;
            }
            else
            {
                printf("Completed! %d (%d + %d) added to the list.\n", value + value2, value, value2);
            }
            break;

        case 4:
            printf("List:\n");
            errorCode = printList(list);
            if (errorCode != 0)
            {
                printf("List not created.\n");
            }
            break;

        case 5:
            printActions();
            break;

        default:
            printf("There is no such command :(\n");
            break;
        }
    }

    freeList(list);
    return 0;
}