#pragma once

#include <stdbool.h>

typedef struct StackElement StackElement;

typedef struct Stack Stack;

// Creating a stack
Stack *createStack();

// Pushing a new element on top of the stack
int push(Stack *stack, int value);

// If the stack exists, it puts the top value of the stack in resultingValue and removes this top element
int pop(Stack *Stack, int *resultingValue);

// If the stack exists, then it returns its length
int lengthStack(Stack *stack);

// If there is an upper element of the stack, then returns it
int top(Stack *stack, int *value);

// Cleaning the stack
int freeStack(Stack *stack);

// If the stack exists, then checks if it is empty
bool isEmpty(Stack *stack);

// If the stack exists, then outputs it
int printStack(Stack *stack);

//Error codes:
// -1: Stack not created
// -2: Stack head is missing(or memory allocation error for head)
// -3: Memory allocation error