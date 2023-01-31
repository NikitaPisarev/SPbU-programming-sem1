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

void freeNode(Tree *tree)
{
    free(tree->key);
    free(tree->value);
    free(tree);
}

void freeTree(Tree *root)
{
    if (root == NULL)
    {
        return;
    }
    freeTree(root->leftChild);
    freeTree(root->rightChild);
    freeNode(root);
}

Tree *createEmptyTree()
{
    return NULL;
}

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
        tree->balance = 0;
        rightChild->balance = 1;
        break;

    case 0:
        tree->balance = 0;
        rightChild->balance = 0;
        break;

    case 1:
        tree->balance = -1;
        rightChild->balance = 0;
        break;
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
        tree->balance = 1;
        leftChild->balance = 0;
        break;

    case 0:
        tree->balance = 0;
        leftChild->balance = 0;
        break;

    case 1:
        tree->balance = 0;
        leftChild->balance = -1;
        break;
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

Tree *insert(Tree *root, char *key, char *value, bool *isClimbing, Error *errorCode)
{
    if (root == NULL)
    {
        Tree *newTree = createTree(key, value);
        if (newTree == NULL)
        {
            *errorCode = MemoryAllocationError;
            *isClimbing = false;
        }
        return newTree;
    }

    int comparisonResult = strcmp(root->key, key);
    int balanceChange = 0;
    if (comparisonResult == 0)
    {
        *isClimbing = false;
        free(root->value);
        root->value = calloc(strlen(value) + 1, sizeof(char));
        if (root->value == NULL)
        {
            *errorCode = MemoryAllocationError;
            *isClimbing = false;
            return NULL;
        }
        strcpy(root->value, value);
        return root;
    }
    else if (comparisonResult > 0)
    {
        root->leftChild = insert(root->leftChild, key, value, isClimbing, errorCode);
        balanceChange = -1;
    }
    else
    {
        root->rightChild = insert(root->rightChild, key, value, isClimbing, errorCode);
        balanceChange = 1;
    }

    if (!*isClimbing)
    {
        return root;
    }

    root->balance = root->balance + balanceChange;
    // -2,2 - after the balancing function, the length will remain the same, therefore further climbing is not necessary
    // 0 - have balanced the tree
    if (root->balance == 0 || root->balance == 2 || root->balance == -2)
    {
        *isClimbing = false;
    }
    return balance(root);
}

Tree *addValue(Tree *tree, char *key, char *value, Error *errorCode)
{
    if (key == NULL || value == NULL)
    {
        return NULL;
    }
    bool isClimbing = true;
    return insert(tree, key, value, &isClimbing, errorCode);
}

Tree *leftMostChild(Tree **tree)
{
    while ((*tree)->rightChild != NULL)
    {
        tree = &(*tree)->rightChild;
    }
    return *tree;
}

Tree *deleteNode(Tree *root, char *key, bool *isClimbing)
{
    if (root == NULL)
    {
        *isClimbing = false;
        return NULL;
    }

    int comparisonResult = strcmp(root->key, key);
    int balanceChange = 0;
    if (comparisonResult == 0)
    {
        if (root->leftChild == NULL)
        {
            *isClimbing = true;
            Tree *deleteElement = root;
            root = root->rightChild;
            freeNode(deleteElement);
            return root;
        }
        if (root->rightChild == NULL)
        {
            *isClimbing = true;
            Tree *deleteElement = root;
            root = root->leftChild;
            freeNode(deleteElement);
            return root;
        }

        Tree *leftLargest = leftMostChild(&root->leftChild);
        char *temporaryValue = root->value;
        root->value = leftLargest->value;
        leftLargest->value = temporaryValue;

        char *temporaryKey = root->key;
        root->key = leftLargest->key;
        leftLargest->key = temporaryKey;

        root->leftChild = deleteNode(root->leftChild, leftLargest->key, isClimbing); //
        balanceChange = 1;
    }
    else if (comparisonResult > 0)
    {
        root->leftChild = deleteNode(root->leftChild, key, isClimbing);
        balanceChange = 1;
    }
    else
    {
        root->rightChild = deleteNode(root->rightChild, key, isClimbing);
        balanceChange = -1;
    }

    if (!*isClimbing)
    {
        return root;
    }

    root->balance = root->balance + balanceChange;
    if (root->balance == 1 || root->balance == -1) // this means that the height of the subtree has not changed and the climbing stops
    {
        *isClimbing = false;
    }
    return balance(root);
}

Tree *deleteElement(Tree *root, char *key)
{
    if (key == NULL)
    {
        return NULL;
    }
    bool isClimbing = true;
    return deleteNode(root, key, &isClimbing);
}

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

bool testGetValue()
{
    Tree *testTree = calloc(1, sizeof(Tree));
    if (testTree == NULL)
    {
        return false;
    }
    testTree->value = calloc(2, sizeof(char));
    if (testTree->value == NULL)
    {
        return false;
    }
    testTree->key = calloc(2, sizeof(char));
    if (testTree->key == NULL)
    {
        return false;
    }
    strcpy(testTree->key, "C");
    strcpy(testTree->value, "C");

    testTree->leftChild = calloc(1, sizeof(Tree));
    if (testTree->leftChild == NULL)
    {
        return false;
    }
    testTree->leftChild->value = calloc(2, sizeof(char));
    if (testTree->leftChild->value == NULL)
    {
        return false;
    }
    testTree->leftChild->key = calloc(2, sizeof(char));
    if (testTree->leftChild->key == NULL)
    {
        return false;
    }
    strcpy(testTree->leftChild->key, "A");
    strcpy(testTree->leftChild->value, "A");

    bool resultTest = strcmp(getValue(testTree, "A"), "A") == 0;
    freeTree(testTree);
    return resultTest;
}

bool testAdd()
{
    Tree *testTree = NULL;
    Error errorCode = Ok;
    testTree = addValue(testTree, "5", "5", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }
    testTree = addValue(testTree, "3", "3", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }
    testTree = addValue(testTree, "7", "7", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }

    bool firstTest = strcmp(getValue(testTree, "5"), "5") == 0;
    bool secondTest = strcmp(getValue(testTree, "3"), "3") == 0;
    bool thirdTest = strcmp(getValue(testTree, "7"), "7") == 0;
    freeTree(testTree);
    return firstTest && secondTest && thirdTest;
}

bool testDelete()
{
    Tree *testTree = NULL;
    Error errorCode = Ok;
    testTree = addValue(testTree, "5", "5", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }
    testTree = addValue(testTree, "3", "3", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }
    testTree = addValue(testTree, "7", "7", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }

    deleteElement(testTree, "5");
    bool firstTest = getValue(testTree, "5") == NULL;
    bool secondTest = strcmp(getValue(testTree, "3"), "3") == 0;
    bool thirdTest = strcmp(getValue(testTree, "7"), "7") == 0;
    freeTree(testTree);
    return firstTest && secondTest && thirdTest;
}

int checkBalancedTree(Tree *tree, bool *isBalanced)
{
    if (tree == NULL)
    {
        return 0;
    }
    int heightLeftChild = checkBalancedTree(tree->leftChild, isBalanced);
    int heightRightChild = checkBalancedTree(tree->rightChild, isBalanced);

    if (tree->balance != (heightRightChild - heightLeftChild))
    {
        *isBalanced = false;
    }

    return (heightLeftChild > heightRightChild ? heightLeftChild : heightRightChild) + 1;
}

bool testBalancedTree()
{
    Tree *testTree = NULL;
    Error errorCode = Ok;
    bool resultTest = true;
    testTree = addValue(testTree, "5", "5", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }
    testTree = addValue(testTree, "2", "2", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }
    testTree = addValue(testTree, "8", "8", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }
    testTree = addValue(testTree, "1", "1", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }
    testTree = addValue(testTree, "3", "3", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }
    checkBalancedTree(testTree, &resultTest);

    testTree = addValue(testTree, "4", "4", &errorCode);
    if (errorCode != Ok)
    {
        return false;
    }
    checkBalancedTree(testTree, &resultTest);

    testTree = deleteElement(testTree, "5");
    checkBalancedTree(testTree, &resultTest);

    freeTree(testTree);
    return resultTest;
}

bool tests()
{
    return testGetValue() && testAdd() && testDelete() && testBalancedTree();
}