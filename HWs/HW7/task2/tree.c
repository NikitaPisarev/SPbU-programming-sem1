#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

typedef struct Tree
{
    char operation;
    int number;
    struct Tree *leftChild;
    struct Tree *rightChild;
} Tree;

Error fillTree(Tree **root, FILE *file)
{
    bool isСontinue = true;
    int errorCode = 0;
    while (isСontinue)
    {
        char currentСharacter = getc(file);
        switch (currentСharacter)
        {
        case ' ':
            continue;

        case '(':
            continue;

        case ')':
            isСontinue = false;
            break;

        case '+':
        case '*':
        case '/':
            (*root) = calloc(1, sizeof(Tree));
            if ((*root) == NULL)
            {
                return MemoryAllocationError;
            }
            (*root)->operation = currentСharacter;

            if (fillTree(&(*root)->leftChild, file) == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }

            if (fillTree(&(*root)->rightChild, file) == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }
            break;
        case '-':
            (*root) = calloc(1, sizeof(Tree));
            if ((*root) == NULL)
            {
                return MemoryAllocationError;
            }

            char nextElement = getc(file);
            ungetc(nextElement, file);
            if (nextElement >= '0' && nextElement <= '9') // Checking if it's a negative number
            {
                (*root)->operation = -1; // The indicator that this node is a number
                ungetc(currentСharacter, file);
                fscanf(file, "%d", &(*root)->number);
                isСontinue = false;
                break;
            }

            (*root)->operation = currentСharacter;
            if (fillTree(&(*root)->leftChild, file) == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }

            if (fillTree(&(*root)->rightChild, file) == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }
            break;

        default: // Numbers
            (*root) = calloc(1, sizeof(Tree));
            if ((*root) == NULL)
            {
                return MemoryAllocationError;
            }

            (*root)->operation = -1; // The indicator that this node is a number
            ungetc(currentСharacter, file);
            fscanf(file, "%d", &(*root)->number);
            isСontinue = false;
            break;
        }
    }

    return Ok;
}

int evaluateTree(Tree *tree)
{
    if (tree == NULL)
    {
        return 0;
    }

    int leftValue = evaluateTree(tree->leftChild);
    int rightValue = evaluateTree(tree->rightChild);

    switch (tree->operation)
    {
    case -1: // Numbers
        return tree->number;

    case '+':
        return leftValue + rightValue;

    case '-':
        return leftValue - rightValue;

    case '*':
        return leftValue * rightValue;

    case '/':
        return leftValue / rightValue;
    }
}

void printExpression(Tree *tree)
{
    if (tree == NULL)
    {
        return;
    }

    if (tree->operation == -1) // This is a number
    {
        printf("%d ", tree->number);
    }
    else
    {
        printf("( %c ", tree->operation);
        printExpression(tree->leftChild);
        printExpression(tree->rightChild);
        printf(") ");
    }
}

void freeTree(Tree **root)
{
    if ((*root) == NULL)
    {
        return;
    }

    freeTree(&(*root)->leftChild);
    freeTree(&(*root)->rightChild);
    free(*root);
}