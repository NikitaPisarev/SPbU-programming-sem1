#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

#define maximumSize 256

bool testAdd()
{
    Tree *tree = NULL;
    add(&tree, 1, "Hello");
    add(&tree, 2, "World");

    bool result = strcmp(getValue(tree, 1), "Hello") == 0 &&
                  strcmp(getValue(tree, 2), "World") == 0;
    freeTree(&tree);
    return result;
}

bool testDelete()
{
    Tree *tree = NULL;
    add(&tree, 5, "Hello");
    add(&tree, 3, "World");
    add(&tree, 10, "It's");
    add(&tree, 7, "Dictionary");

    deleteElement(&tree, 10);
    bool result = strcmp(getValue(tree, 5), "Hello") == 0 &&
                  strcmp(getValue(tree, 3), "World") == 0 &&
                  strcmp(getValue(tree, 7), "Dictionary") == 0 &&
                  getValue(tree, 10) == NULL;
    freeTree(&tree);
    return result;
}

bool testsPassed()
{
    return testAdd() && testDelete();
}

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
    if (!testsPassed())
    {
        printf("Tests failed.\n");
        return 0;
    }

    Tree *tree = NULL;
    printf("Hi, it's a dictionary, that's what I can do:\n");
    printActions();

    int action = -1;
    bool isContinue = true;
    int key = 0;
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
            char buffer[maximumSize] = {0};
            printf("Enter the key and value: ");
            scanf("%d", &key);
            scanf("%s", buffer);
            if (add(&tree, key, buffer) != Ok)
            {
                printf("Memory allocation error.\n");
                isContinue = false;
            }
            break;

        case 2:
            printf("Enter the key: ");
            scanf("%d", &key);
            char *pointerValue = getValue(tree, key);
            if (pointerValue == NULL)
            {
                printf("There is no such key in the dictionary.\n");
            }
            else
            {
                printf("The value under key %d is %s\n", key, pointerValue);
            }
            break;

        case 3:
            printf("Enter the key: ");
            scanf("%d", &key);
            if (getValue(tree, key) == NULL)
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
            scanf("%d", &key);
            deleteElement(&tree, key);
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

    freeTree(&tree);
    return 0;
}