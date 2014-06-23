#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 1000

void push(void*);
void* pop();
void empty_stack();
int is_stack_empty();
int is_stack_full();

#endif

