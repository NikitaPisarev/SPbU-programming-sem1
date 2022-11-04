#define _CRT_SECURE_NO_WARNINGS
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
    printf(" 5 - View the list of commands\n");
    printf(" ---------------------------------------------------------------\n");
}

int main()
{
    Tree *tree = NULL;
    printf("Hi, it's a dictionary, that's what I can do:\n");
    printActions();

    int action = -1;
    bool isContinue = true;
    while (isContinue)
    {
        printf("Enter the command number: ");
        scanf("%d", &action);

        switch (action)
        {
        case 0:
            printf("Good luck!\n");
            freeTree(&tree);
            isContinue = false;
            break;

        case 1:
            int key = 0;
            char buffer[maximumSize] = {0};
            printf("Enter the key and value: ");
            scanf("%d", &key);
            scanf("%s", buffer);
            add(&tree, key, buffer);
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            printf("Tree:\n");
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

    return 0;
}