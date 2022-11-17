#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

typedef struct Tree
{
    char *key;
    char *value;
    int balance;
    struct Tree *leftChild;
    struct Tree *rightChild;
} Tree;

Tree *createTree(char *key, char *value)
{
    Tree *newTree = calloc(1, sizeof(Tree));
    if (newTree == NULL)
    {
        return NULL;
    }
    newTree->key = calloc(strlen(key) + 1, sizeof(char));
    if (newTree->key == NULL)
    {
        return NULL;
    }
    newTree->value = calloc(strlen(value) + 1, sizeof(char));
    if (newTree->value == NULL)
    {
        return NULL;
    }

    strcpy(newTree->value, value);
    strcpy(newTree->key, key);
    newTree->balance = 0;
    return newTree;
}

Tree *rotateLeft(Tree *tree)
{
    Tree *rightChild = tree->rightChild;
    Tree *leftFromRightChild = rightChild->leftChild;
    rightChild->leftChild = tree;
    tree->rightChild = leftFromRightChild;
    if (rightChild->balance == 0)
    {
        tree->balance = 1;
        rightChild->balance = -1;
    }
    else
    {
        tree->balance = 0;
        rightChild->balance = 0;
    }

    return rightChild;
}

Tree *rotateRight(Tree *tree)
{
    Tree *leftChild = tree->leftChild;
    Tree *rightFromLeftChild = leftChild->rightChild;
    leftChild->rightChild = tree;
    tree->leftChild = rightFromLeftChild;
    if (leftChild->balance == 0)
    {
        tree->balance = -1;
        leftChild->balance = 1;
    }
    else
    {
        tree->balance = 0;
        leftChild->balance = 0;
    }

    return leftChild;
}

Tree *balance(Tree *tree)
{
    if (tree->balance == 2)
    {
        if (tree->rightChild->balance >= 0)
        {
            return rotateLeft(tree);
        }
        tree->rightChild = rotateRight(tree->rightChild);
        return rotateLeft(tree);
    }

    if (tree->balance == -2)
    {
        if (tree->leftChild->balance <= 0)
        {
            return rotateRight(tree);
        }
        tree->leftChild = rotateLeft(tree->rightChild);
        return rotateRight(tree);
    }

    return tree;
}

Tree *insert(Tree *root, char *key, char *value)
{
    if (root == NULL)
    {
        return createTree(key, value);
    }

    int comparisonResult = strcmp(root->key, key);
    if (comparisonResult == 0)
    {
        free(root->value);
        root->value = calloc(strlen(value) + 1, sizeof(char));
        if (root->value == NULL)
        {
            return NULL;
        }
        strcpy(root->value, value);
        return root;
    }
    if (comparisonResult > 0)
    {
        if (root->leftChild == NULL)
        {
            root->leftChild = insert(root->leftChild, key, value);
            --root->balance;
            return balance(root);
        }

        int previousBalanceLeft = root->leftChild->balance;
        root->leftChild = insert(root->leftChild, key, value);
        int currentBalanceLeft = root->leftChild->balance;

        if (previousBalanceLeft == 0 && currentBalanceLeft != 0)
        {
            --root->balance;
        }
        return balance(root);
    }
    if (root->rightChild == NULL)
    {
        root->rightChild = insert(root->rightChild, key, value);
        ++root->balance;
        return balance(root);
    }

    int previousBalanceRight = root->rightChild->balance;
    root->rightChild = insert(root->rightChild, key, value);
    int currentBalanceRight = root->rightChild->balance;

    if (previousBalanceRight == 0 && currentBalanceRight != 0)
    {
        ++root->balance;
    }
    return balance(root);
}

// Tree **leftMostChild(Tree **tree)
// {
//     while ((*tree)->rightChild != NULL)
//     {
//         tree = &(*tree)->rightChild;
//     }
//     return tree;
// }

// char *getValue(Tree *tree, int key)
// {
//     if (tree == NULL)
//     {
//         return NULL;
//     }
//     if (tree->key == key)
//     {
//         return tree->value;
//     }

//     if (tree->key > key)
//     {
//         getValue(tree->leftChild, key);
//     }
//     else
//     {
//         getValue(tree->rightChild, key);
//     }
// }

void printTree(Tree *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%s: %s\n", root->key, root->value);
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
    free((*root)->value);
    free((*root));
}