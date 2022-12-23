#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void getMinimumsElementsLines(int **matrix, int linesAmount, int amountColumns, int *minimumsElelemntsLines)
{
    for (int i = 0; i < linesAmount; ++i)
    {
        minimumsElelemntsLines[i] = matrix[i][0];
        for (int j = 0; j < amountColumns; ++j)
        {
            if (matrix[i][j] < minimumsElelemntsLines[i])
            {
                minimumsElelemntsLines[i] = matrix[i][j];
            }
        }
    }
}

void getMaximumsElementsColumns(int **matrix, int linesAmount, int amountColumns, int *maximumsElementsColumns)
{
    for (int i = 0; i < amountColumns; ++i)
    {
        maximumsElementsColumns[i] = matrix[0][i];
        for (int j = 0; j < linesAmount; ++j)
        {
            if (matrix[j][i] > maximumsElementsColumns[i])
            {
                maximumsElementsColumns[i] = matrix[j][i];
            }
        }
    }
}

bool findSaddlePoints(int **matrix, int linesAmount, int amountColumns, int *maximumsElementsColumns, int *minimumsElementsLines)
{
    bool isFound = false;
    for (int i = 0; i < linesAmount; i++)
    {
        for (int j = 0; j < amountColumns; j++)
        {
            if (minimumsElementsLines[i] == maximumsElementsColumns[j])
            {
                printf("(%d, %d); ", i, j);
                isFound = true;
            }
        }
    }
    printf("\n");
    return isFound;
}

void printMatrix(int **matrix, int amountLines, int amountColumns)
{
    for (int i = 0; i < amountLines; ++i)
    {
        for (int j = 0; j < amountColumns; ++j)
        {
            printf("%d\t|", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int **matrix, int amountLines)
{
    for (int i = 0; i < amountLines; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int main()
{
    FILE *file = fopen("../HWs/Test3.1/task2/matrix.txt", "r");
    if (file == NULL)
    {
        printf("File opening error\n");
        return -1;
    }

    int amountLines = 0;
    int amountColumns = 0;
    int scanResult = fscanf(file, "%d %d", &amountLines, &amountColumns);
    if (scanResult == 0 || amountColumns <= 0 || amountColumns <= 0)
    {
        printf("Incorrect file structure.\n");
        return -1;
    }
    int **matrix = calloc(amountLines, sizeof(int));
    if (matrix == NULL)
    {
        printf("Memory allocation error.\n");
        return -1;
    }
    for (int i = 0; i < amountLines; ++i)
    {
        matrix[i] = calloc(amountColumns, sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Memory allocation error.\n");
            freeMatrix(matrix, amountLines);
            return -1;
        }
        for (int j = 0; j < amountColumns; ++j)
        {
            scanResult = fscanf(file, "%d", &matrix[i][j]);
            if (scanResult == 0)
            {
                freeMatrix(matrix, amountLines);
                printf("Incorrect file structure.\n");
                return -1;
            }
        }
    }
    char extraСharacter = fgetc(file);
    if (extraСharacter != EOF)
    {
        freeMatrix(matrix, amountLines);
        printf("Incorrect file structure.\n");
        return -1;
    }
    printf("Your matrix:\n");
    printMatrix(matrix, amountLines, amountColumns);

    int *minimumsElementsLines = calloc(amountLines, sizeof(int));
    if (minimumsElementsLines == NULL)
    {
        printf("Memory allocation error.\n");
        freeMatrix(matrix, amountLines);
        return -1;
    }
    getMinimumsElementsLines(matrix, amountLines, amountColumns, minimumsElementsLines);
    int *maximumsElementsColumns = calloc(amountColumns, sizeof(int));
    if (maximumsElementsColumns == NULL)
    {
        printf("Memory allocation error.\n");
        freeMatrix(matrix, amountLines);
        free(minimumsElementsLines);
        return -1;
    }
    getMaximumsElementsColumns(matrix, amountLines, amountColumns, maximumsElementsColumns);
    printf("Information about saddle points:\n");
    int isFound = findSaddlePoints(matrix, amountLines, amountColumns, maximumsElementsColumns, minimumsElementsLines);
    if (!isFound)
    {
        printf("No saddle points.\n");
    }

    freeMatrix(matrix, amountLines);
    free(minimumsElementsLines);
    free(maximumsElementsColumns);
    return 0;
}