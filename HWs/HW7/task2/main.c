#include <stdio.h>
#include "tree.h"

int main()
{
    Tree *tree = NULL;
    FILE *file = fopen("data.txt", "r");
    if (file == NULL || feof(file))
    {
        printf("Error opening the file (or the file is empty).\n");
        return 0;
    }

    if (fillTree(&tree, file) == MemoryAllocationError)
    {
        freeTree(&tree);
        printf("Memory allocation error.\n");
        return 0;
    }
    fclose(file);

    printExpression(tree);
    printf("= %d", evaluateTree(tree));
    freeTree(&tree);
    return 0;
}