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

Stack *stackCreate()
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

int pop(Stack *stack)
{
    if (stack == NULL || stack->head == NULL)
    {
        return -1;
    }

    int element = stack->head->value;


}

int top(Stack *stack)
{
    if (stack == NULL || stack->head == NULL)
    {
        return -1;
    }

    return stack->head->value;
}

int isEmpty(Stack *stack)
{
    if (stack == NULL)
    {
        return -1;
    }

    return stack->head == NULL;
}

void main()
{
    Stack *stack = stackCreate();
}