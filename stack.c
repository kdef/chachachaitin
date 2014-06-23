#include <stdlib.h>
#include "stack.h"

// stack.c

#define EMPTY_STACK -1

int top = EMPTY_STACK;

// make some room for the stack
void* stack[MAX_STACK_SIZE];

void push(void* item) {
    stack[++top] = item;
}

void* pop() {
    return stack[top--];
}

void empty_stack() {
    top = EMPTY_STACK;
}

int is_stack_empty() {
    return top == EMPTY_STACK;
}

int is_stack_full() {
    return (top + 1) == MAX_STACK_SIZE;
}

