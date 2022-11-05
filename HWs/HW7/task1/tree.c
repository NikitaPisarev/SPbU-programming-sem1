#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
    Ok,
    MemoryAllocationError
} Error;

typedef struct Tree
{
    int key;
    char *value;
    struct Tree *leftChild;
    struct Tree *rightChild;
} Tree;

Error add(Tree **root, int key, char *value)
{
    if ((*root) == NULL)
    {
        (*root) = calloc(1, sizeof(Tree));
        if ((*root) == NULL)
        {
            return MemoryAllocationError;
        }
        (*root)->key = key;
        (*root)->value = calloc(strlen(value) + 1, sizeof(char));
        if ((*root)->value == NULL)
        {
            return MemoryAllocationError;
        }
        strcpy((*root)->value, value);
        return Ok;
    }

    if ((*root)->key == key)
    {
        free((*root)->value);
        (*root)->value = calloc(strlen(value) + 1, sizeof(char));
        if ((*root)->value == NULL)
        {
            return MemoryAllocationError;
        }
        strcpy((*root)->value, value);
        return Ok;
    }

    if ((*root)->key > key)
    {
        add(&(*root)->leftChild, key, value);
    }
    else
    {
        add(&(*root)->rightChild, key, value);
    }
}

Tree **leftMostChild(Tree **tree)
{
    while ((*tree)->rightChild != NULL)
    {
        tree = &(*tree)->rightChild;
    }
    return tree;
}

void deleteElement(Tree **root, int key)
{
    if ((*root) == NULL)
    {
        return;
    }

    if ((*root)->key == key)
    {
        if ((*root)->leftChild == NULL)
        {
            Tree *elementToDelete = (*root);
            (*root) = (*root)->rightChild;
            free(elementToDelete);
            return;
        }

        Tree **leftLargest = leftMostChild(&(*root)->leftChild);
        char *temporaryValue = (*root)->value;
        (*root)->value = (*leftLargest)->value;
        (*leftLargest)->value = temporaryValue;

        int temporaryKey = (*root)->key;
        (*root)->key = (*leftLargest)->key;
        (*leftLargest)->key = temporaryKey;

        Tree *elementToDelete = (*leftLargest);
        (*leftLargest) = (*leftLargest)->leftChild;
        free(elementToDelete->value);
        free(elementToDelete);
        return;
    }

    if ((*root)->key > key)
    {
        deleteElement(&(*root)->leftChild, key);
    }
    else
    {
        deleteElement(&(*root)->rightChild, key);
    }
}

char *getValue(Tree *tree, int key)
{
    if (tree == NULL)
    {
        return NULL;
    }
    if (tree->key == key)
    {
        return tree->value;
    }

    if (tree->key > key)
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

    printf("%d: %s\n", root->key, root->value);
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