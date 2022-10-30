#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct StackElement
{
    int value;
    struct StackElement *next;
} StackElement;

typedef struct Stack
{
    StackElement *head;
} Stack;

Stack *createStack()
{
    Stack *stack = calloc(1, sizeof(Stack));

    if (stack == NULL)
    {
        return NULL;
    }

    return stack;
}

int push(Stack *stack, int value)
{
    if (stack == NULL)
    {
        return -1;
    }

    if (stack->head == NULL)
    {
        stack->head = calloc(1, sizeof(StackElement));
        if (stack->head == NULL)
        {
            return -2;
        }

        stack->head->value = value;
        return 0;
    }

    StackElement *newElement = calloc(1, sizeof(StackElement));

    if (newElement == NULL)
    {
        return -3;
    }

    newElement->value = value;
    newElement->next = stack->head;
    stack->head = newElement;

    return 0;
}

int pop(Stack *stack, int *resultingValue)
{
    if (stack == NULL)
    {
        return -1;
    }

    if (stack->head == NULL)
    {
        return -2;
    }

    StackElement *nextElement = stack->head->next;

    *resultingValue = stack->head->value;
    free(stack->head);

    stack->head = nextElement;

    return 0;
}

int lengthStack(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }

    int length = 0;
    StackElement *currentElement = stack->head;

    while (currentElement != NULL)
    {
        ++length;
        currentElement = currentElement->next;
    }

    return length;
}

int top(Stack *stack, int *value)
{
    if (stack == NULL)
    {
        return -1;
    }

    if (stack->head == NULL)
    {
        return -2;
    }

    *value = stack->head->value;

    return 0;
}

void freeStack(Stack *stack)
{
    if (stack == NULL)
    {
        return;
    }

    StackElement *currentElement = stack->head;

    while (currentElement != NULL)
    {
        StackElement *nextElement = currentElement->next;
        free(currentElement);
        currentElement = nextElement;
    }
    free(stack);
}

bool isEmpty(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }

    return stack->head == NULL;
}

int printStack(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }

    StackElement *currentElement = stack->head;

    while (currentElement != NULL)
    {
        printf("%d ", currentElement->value);

        currentElement = currentElement->next;
    }
    printf("\n");

    return 0;
}