#include "list.h"

#ifndef STACK_H
#define STACK_H

#define stack_empty(stack) ((stack)->size == 0)

#define stack_destroy list_destroy

#define stack_push list_push_front

typedef struct List Stack;

void stack_init(Stack *stack, int n);

DataType stack_pop(Stack *stack);

#endif  // STACK_H