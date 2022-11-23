#pragma once

typedef struct StackElement StackElement;

typedef struct Stack Stack;

Stack *createStack();

int push(Stack *stack, int value);

int pop(Stack *stack, int *returnValue);

int add(Stack *stack);

void printStack(Stack *stack);

void freeStack(Stack *stack);