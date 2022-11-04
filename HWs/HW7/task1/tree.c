#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Tree
{
    int key;
    char *value;
    struct Tree *leftChild;
    struct Tree *rightChild;
} Tree;

void add(Tree **root, int key, char *value)
{
    if ((*root) == NULL)
    {
        (*root) = calloc(1, sizeof(Tree));
        if ((*root) == NULL)
        {
            return;
        }
        (*root)->key = key;
        (*root)->value = calloc(strlen(value) + 1, sizeof(char));
        if ((*root)->value == NULL)
        {
            return;
        }
        strcpy((*root)->value, value);
        return;
    }

    if ((*root)->key == key)
    {
        (*root)->value = calloc(strlen(value) + 1, sizeof(char));
        if ((*root)->value == NULL)
        {
            return;
        }
        strcpy((*root)->value, value);
        return;
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

void freeTree(Tree **root)
{
    if ((*root) == NULL)
    {
        return;
    }

    freeTree(&(*root)->leftChild);
    freeTree(&(*root)->rightChild);
    free((*root));
}

void printTree(Tree *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%s ", root->value);
    printTree(root->leftChild);
    printTree(root->rightChild);
}