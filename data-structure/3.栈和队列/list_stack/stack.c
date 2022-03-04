#include "stack.h"

void stack_init(Stack *stack, int n) { list_init(stack); }

DataType stack_pop(Stack *stack) {
    DataType x = stack->head->data;
    list_pop_front(stack);

    return x;
}