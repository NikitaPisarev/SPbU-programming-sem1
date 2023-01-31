#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

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
        return -2;
    }
    newElement->value = value;
    newElement->next = stack->head;
    stack->head = newElement;
    return 0;
}

int pop(Stack *stack, int *returnValue)
{
    if (stack == NULL)
    {
        return -1;
    }
    if (stack->head == NULL)
    {
        return -2;
    }
    *returnValue = stack->head->value;

    StackElement *nextElement = stack->head->next;
    free(stack->head);
    stack->head = nextElement;
    return 0;
}

int add(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }
    if (stack->head == NULL)
    {
        return -2;
    }
    if (stack->head->next == NULL)
    {
        return -3;
    }
    StackElement *firstElement = stack->head;
    StackElement *secondElement = stack->head->next;
    secondElement->value += firstElement->value;
    free(firstElement);
    stack->head = secondElement;
    return 0;
}

void printStack(Stack *stack)
{
    if (stack == NULL)
    {
        return;
    }
    StackElement *currentElement = stack->head;
    while (currentElement != NULL)
    {
        printf("%d ", currentElement->value);
        currentElement = currentElement->next;
    }
    printf("\n");
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