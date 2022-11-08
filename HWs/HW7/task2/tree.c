#include <stdio.h>
#include <string.h>
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

int fillTree(Tree **root, FILE *fileName)
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
        case '-':
        case '*':
        case '/':
            (*root) = calloc(1, sizeof(Tree));
            if ((*root) == NULL)
            {
                return -1;
            }
            (*root)->element = currentСharacter;

            errorCode = fillTree(&(*root)->leftChild, fileName);
            if (errorCode != 0)
            {
                return errorCode;
            }
            errorCode = fillTree(&(*root)->rightChild, fileName);
            if (errorCode != 0)
            {
                return errorCode;
            }
            break;

        default: // numbers
            ungetc(currentСharacter, fileName);
            (*root) = calloc(1, sizeof(Tree));
            if ((*root) == NULL)
            {
                return -1;
            }
            (*root)->element = -1; // Shows that in this node the number
            fscanf(fileName, "%d", &(*root)->value);
            isСontinue = false;
            break;
        }
    }

    return 0;
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
        break;

    case '+':
        return leftValue + rightValue;
        break;

    case '-':
        return leftValue - rightValue;
        break;

    case '*':
        return leftValue * rightValue;
        break;

    case '/':
        return leftValue / rightValue;
        break;
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

void printTree(Tree *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->element == -1)
    {
        printf("%d ", root->value);
    }
    else
    {
        printf("%c ", root->element);
    }
    printf("\n");
    printTree(root->leftChild);
    printTree(root->rightChild);
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