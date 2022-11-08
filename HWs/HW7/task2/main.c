#include <stdio.h>
#include "tree.h"

int main()
{
    Tree *tree = NULL;
    FILE *file = fopen("../HWs/HW7/task2/data.txt", "r");
    if (file == NULL || feof(file))
    {
        printf("File error.\n");
        return 0;
    }

    if (fillTree(&tree, file) != 0)
    {
        printf("Function error.\n");
        return 0;
    }

    printExpression(tree);
    return 0;
}