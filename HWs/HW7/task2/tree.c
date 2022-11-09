#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

typedef struct Tree
{
    char element;
    int value;
    struct Tree *leftChild;
    struct Tree *rightChild;
} Tree;

Error fillTree(Tree **root, FILE *fileName)
{
    bool isСontinue = true;
    int errorCode = 0;
    while (isСontinue)
    {
        char currentСharacter = getc(fileName);
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
            (*root)->element = currentСharacter;

            if (fillTree(&(*root)->leftChild, fileName) == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }

            if (fillTree(&(*root)->rightChild, fileName) == MemoryAllocationError)
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

            char nextElement = getc(fileName);
            ungetc(nextElement, fileName);
            if (nextElement >= '0' && nextElement <= '9') // Checking if it's a negative number
            {
                (*root)->element = -1; // The indicator that this node is a number
                ungetc(currentСharacter, fileName);
                fscanf(fileName, "%d", &(*root)->value);
                isСontinue = false;
                break;
            }

            (*root)->element = currentСharacter;
            if (fillTree(&(*root)->leftChild, fileName) == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }

            if (fillTree(&(*root)->rightChild, fileName) == MemoryAllocationError)
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

            (*root)->element = -1; // The indicator that this node is a number
            ungetc(currentСharacter, fileName);
            fscanf(fileName, "%d", &(*root)->value);
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

    switch (tree->element)
    {
    case -1: // Numbers
        return tree->value;

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

    if (tree->element == -1) // This is a number
    {
        printf("%d ", tree->value);
    }
    else
    {
        printf("( %c ", tree->element);
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