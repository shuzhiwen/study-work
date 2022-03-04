#include "vector.h"

#ifndef STACK_H
#define STACK_H

#define stack_init vector_init

#define stack_destroy vector_destroy

#define stack_size vector_size

#define stack_empty(stack) ((stack)->size == 0)

#define stack_push vector_push_back

#define stack_peek(stack) (stack)->buffer[(stack)->size - 1]

typedef struct Vector Stack;

DataType stack_top(Stack *stack);

DataType stack_pop(Stack *stack);

#endif  // STACK_H