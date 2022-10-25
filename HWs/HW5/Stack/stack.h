#pragma once

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
int top(Stack *stack);

// Cleaning the stack
int freeStack(Stack *stack);