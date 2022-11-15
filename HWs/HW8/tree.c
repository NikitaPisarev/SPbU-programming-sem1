#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

typedef struct Tree
{
    char *key;
    char *value;
    int balance;
    struct Tree *leftChild;
    struct Tree *rightChild;
} Tree;

Tree *findTree(Tree *root, char *key)
{
    if (root == NULL)
        return NULL;

    if (strcmp(key, root->key) == 0)
        return root;

    return strcmp(root->key, key) > 0 ? findTree(root->leftChild, key) : findTree(root->rightChild, key);
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

Tree *addTree(Tree *root, char *key, char *value)
{
    if (root == NULL)
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

    if (strcmp(root->key, key) > 0)
    {
        root->leftChild = addTree(root->leftChild, key, value);
        --root->balance;
    }
    else
    {
        root->rightChild = addTree(root->rightChild, key, value);
        ++root->balance;
    }

    return balance(root);
}

Tree *insert(Tree *root, char *key, char *value)
{
    Tree *foundTree = findTree(root, key);
    if (foundTree != NULL)
    {
        free(foundTree->value);
        foundTree->value = calloc(strlen(value) + 1, sizeof(char));
        if (foundTree->value == NULL)
        {
            return NULL;
        }
        strcpy(foundTree->value, value);
        return root;
    }
    return addTree(root, key, value);
}

// Tree **leftMostChild(Tree **tree)
// {
//     while ((*tree)->rightChild != NULL)
//     {
//         tree = &(*tree)->rightChild;
//     }
//     return tree;
// }

// void deleteElement(Tree **root, int key)
// {
//     if ((*root) == NULL)
//     {
//         return;
//     }

//     if ((*root)->key == key)
//     {
//         if ((*root)->leftChild == NULL)
//         {
//             Tree *elementToDelete = (*root);
//             (*root) = (*root)->rightChild;
//             free(elementToDelete->value);
//             free(elementToDelete);
//             return;
//         }

//         Tree **leftLargest = leftMostChild(&(*root)->leftChild);
//         char *temporaryValue = (*root)->value;
//         (*root)->value = (*leftLargest)->value;
//         (*leftLargest)->value = temporaryValue;

//         int temporaryKey = (*root)->key;
//         (*root)->key = (*leftLargest)->key;
//         (*leftLargest)->key = temporaryKey;

//         Tree *elementToDelete = (*leftLargest);
//         (*leftLargest) = (*leftLargest)->leftChild;
//         free(elementToDelete->value);
//         free(elementToDelete);
//         return;
//     }

//     if ((*root)->key > key)
//     {
//         deleteElement(&(*root)->leftChild, key);
//     }
//     else
//     {
//         deleteElement(&(*root)->rightChild, key);
//     }
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