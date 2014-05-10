#ifndef STACK_H
#define STACK_H

#include "graph.h"

#define MAX_STACK_SIZE 1000
typedef vertex stack_type;

void push(stack_type*);
stack_type* pop();
void empty_stack();
int is_stack_empty();
int is_stack_full();

#endif

