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

Tree *bigRotateLeft(Tree *tree)
{
    Tree *rightChild = tree->rightChild;
    Tree *leftFromRightChild = rightChild->leftChild;
    Tree *leftFromLeftChild = leftFromRightChild->leftChild;
    Tree *rightFromLeftChild = leftFromRightChild->rightChild;
    leftFromRightChild->leftChild = tree;
    leftFromRightChild->rightChild = rightChild;
    tree->rightChild = leftFromLeftChild;
    rightChild->leftChild = rightFromLeftChild;
    switch (leftFromRightChild->balance)
    {
    case -1:
    {
        tree->balance = 0;
        rightChild->balance = 1;
        break;
    }
    case 0:
    {
        tree->balance = 0;
        rightChild->balance = 0;
        break;
    }
    case 1:
    {
        tree->balance = -1;
        rightChild->balance = 0;
        break;
    }
    }
    leftFromRightChild->balance = 0;

    return leftFromRightChild;
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

Tree *bigRotateRight(Tree *tree)
{
    Tree *leftChild = tree->leftChild;
    Tree *rightFromLeftChild = leftChild->rightChild;
    Tree *rightFromRightChild = rightFromLeftChild->rightChild;
    Tree *leftFromRightChild = rightFromLeftChild->leftChild;
    rightFromLeftChild->leftChild = leftChild;
    rightFromLeftChild->rightChild = tree;
    tree->leftChild = rightFromRightChild;
    leftChild->rightChild = leftFromRightChild;
    switch (rightFromLeftChild->balance)
    {
    case -1:
    {
        tree->balance = 1;
        leftChild->balance = 0;
        break;
    }
    case 0:
    {
        tree->balance = 0;
        leftChild->balance = 0;
        break;
    }
    case 1:
    {
        tree->balance = 0;
        leftChild->balance = -1;
        break;
    }
    }
    rightFromLeftChild->balance = 0;

    return rightFromLeftChild;
}

Tree *balance(Tree *tree)
{
    if (tree->balance == 2)
    {
        if (tree->rightChild->balance >= 0)
        {
            return rotateLeft(tree);
        }
        return bigRotateLeft(tree);
    }

    if (tree->balance == -2)
    {
        if (tree->leftChild->balance <= 0)
        {
            return rotateRight(tree);
        }
        return bigRotateRight(tree);
    }

    return tree;
}

Tree *insert(Tree *root, char *key, char *value, bool *isClimbing)
{
    if (root == NULL)
    {
        return createTree(key, value);
    }

    int comparisonResult = strcmp(root->key, key);
    int movement = 0;
    if (comparisonResult == 0)
    {
        *isClimbing = false;
        free(root->value);
        root->value = calloc(strlen(value) + 1, sizeof(char));
        if (root->value == NULL)
        {
            return NULL;
        }
        strcpy(root->value, value);
        return root;
    }
    else if (comparisonResult > 0)
    {
        root->leftChild = insert(root->leftChild, key, value, isClimbing);
        movement = -1;
    }
    else
    {
        root->rightChild = insert(root->rightChild, key, value, isClimbing);
        movement = 1;
    }

    if (!*isClimbing)
    {
        return root;
    }

    root->balance = root->balance + movement;
    if (root->balance == 0 || root->balance == -2 || root->balance == 2)
    {
        *isClimbing = false;
    }
    return balance(root);
}

Tree *addValue(Tree *tree, char *key, char *value)
{
    if (key == NULL || value == NULL)
    {
        return NULL;
    }
    bool isClimbing = true;
    return insert(tree, key, value, &isClimbing);
}

Tree *deleteElement(Tree *root, char *key);

char *getValue(Tree *tree, char *key)
{
    if (tree == NULL)
    {
        return NULL;
    }

    int comparisonResult = strcmp(tree->key, key);
    if (comparisonResult == 0)
    {
        return tree->value;
    }
    if (comparisonResult > 0)
    {
        getValue(tree->leftChild, key);
    }
    else
    {
        getValue(tree->rightChild, key);
    }
}

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

void freeTree(Tree *root)
{
    if (root == NULL)
    {
        return;
    }

    freeTree(root->leftChild);
    freeTree(root->rightChild);
    free(root->key);
    free(root->value);
    free(root);
}