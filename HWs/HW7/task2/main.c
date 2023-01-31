#include <stdio.h>
#include <stdbool.h>
#include "tree.h"

bool test1()
{
    char tests[] = "(* (+ -10 -2) 3)";
    Tree *tree = NULL;
    FILE *fileOut = fopen("test.txt", "w");
    if (fileOut == NULL)
    {
        printf("File opening error.\n");
        return false;
    }
    fprintf(fileOut, "%s", tests);
    fclose(fileOut);

    FILE *fileIn = fopen("test.txt", "r");
    if (fileIn == NULL)
    {
        printf("File opening error.\n");
        return false;
    }

    if (fillTree(&tree, fileIn) == MemoryAllocationError)
    {
        fclose(fileIn);
        freeTree(&tree);
        printf("Memory allocation error.\n");
        return false;
    }
    fclose(fileIn);

    int answer = evaluateTree(tree);
    freeTree(&tree);
    return answer == -36;
}

bool test2()
{
    char tests[] = "(/ (* 5 10) (+ (- 10 3) (* 1 3)))";
    Tree *tree = NULL;
    FILE *fileOut = fopen("test.txt", "w");
    if (fileOut == NULL)
    {
        printf("File opening error.\n");
        return false;
    }
    fprintf(fileOut, "%s", tests);
    fclose(fileOut);

    FILE *fileIn = fopen("test.txt", "r");
    if (fileIn == NULL)
    {
        printf("File opening error.\n");
        return false;
    }

    if (fillTree(&tree, fileIn) == MemoryAllocationError)
    {
        fclose(fileIn);
        freeTree(&tree);
        printf("Memory allocation error.\n");
        return 0;
    }
    fclose(fileIn);

    int answer = evaluateTree(tree);
    freeTree(&tree);
    return answer == 5;
}

bool tests()
{
    return test1() && test2();
}

int main()
{
    if (!tests())
    {
        printf("Tests failed.\n");
        return 0;
    }

    Tree *tree = NULL;
    FILE *file = fopen("../HWs/HW7/task2/data.txt", "r");
    if (file == NULL || feof(file))
    {
        printf("File opening error (or the file is empty).\n");
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