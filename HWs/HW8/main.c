#include <stdio.h>
#include <stdbool.h>
#include "tree.h"

#define maximumSize 256

void printActions(void)
{
    printf(" ---------------------------------------------------------------\n");
    printf(" 0 - Exit\n");
    printf(" 1 - Add a value for a given key to the dictionary\n");
    printf(" 2 - Get the value for a given key from the dictionary\n");
    printf(" 3 - Check the presence of the specified key in the dictionary\n");
    printf(" 4 - Delete the key and its associated value from the dictionary\n");
    printf(" 5 - Print the dictionary\n");
    printf(" 6 - View the list of commands\n");
    printf(" ---------------------------------------------------------------\n");
}

int main()
{
    if (!tests())
    {
        printf("Tests failed.\n");
        return 0;
    }

    Tree *tree = NULL;
    printf("Hi, it's a dictionary, that's what I can do:\n");
    printActions();

    int action = -1;
    bool isContinue = true;
    char bufferKey[maximumSize] = {0};
    char bufferValue[maximumSize] = {0};
    while (isContinue)
    {
        printf("Enter the command number: ");
        scanf("%d", &action);

        switch (action)
        {
        case 0:
            printf("Good luck!\n");
            isContinue = false;
            break;

        case 1:
            printf("Enter the key and value: ");
            scanf("%s", bufferKey);
            scanf("%s", bufferValue);
            Error errorCode = Ok;
            tree = addValue(tree, bufferKey, bufferValue, &errorCode);
            if (errorCode != Ok)
            {
                printf("Memory allocation error.\n");
                isContinue = false;
            }
            break;

        case 2:
            printf("Enter the key: ");
            scanf("%s", bufferKey);
            char *pointerValue = getValue(tree, bufferKey);
            if (pointerValue == NULL)
            {
                printf("There is no such key in the dictionary.\n");
            }
            else
            {
                printf("The value under key %s is %s\n", bufferKey, pointerValue);
            }
            break;

        case 3:
            printf("Enter the key: ");
            scanf("%s", bufferKey);
            if (getValue(tree, bufferKey) == NULL)
            {
                printf("There is NO such key in the dictionary.\n");
            }
            else
            {
                printf("There is such a key in the dictionary.\n");
            }
            break;

        case 4:
            printf("Enter the key: ");
            scanf("%s", bufferKey);
            tree = deleteElement(tree, bufferKey);
            break;

        case 5:
            printf("Dictionary:\n");
            printTree(tree);
            printf("\n");
            break;

        case 6:
            printActions();
            break;

        default:
            printf("There is no such command :(\n");
            break;
        }
    }

    freeTree(tree);
    return 0;
}
