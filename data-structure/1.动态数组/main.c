#include <stdio.h>

#include "vector.c"
#include "vector.h"

int main() {
    struct vector v, a, b;
    int i;

    vector_new(&v, 10);
    vector_new(&a, 10);
    vector_new(&b, 10);

    for (i = 5; i < 12; i++) {
        vector_push_back(&v, i);
    }
    for (i = 0; i < 5; i++) {
        vector_push_back(&a, i);
    }
    for (i = 2; i < 7; i++) {
        vector_push_back(&b, i);
    }

    printf("Original vector a : ");
    vector_print(&a);
    vector_reverse(&a);
    printf("Inversion : ");
    vector_print(&a);
    printf("\n");

    printf("Original vector a : ");
    vector_print(&a);
    printf("Original vector b : ");
    vector_print(&b);
    vector_swap(&a, &b);
    printf("Vector a after exchange : ");
    vector_print(&a);
    printf("Vector b after exchange : ");
    vector_print(&b);
    printf("\n");

    printf("Original capacity of vector v : %d\n", v.capacity);
    printf("Original size of vector v : %d\n", v.size);
    vector_shrink_to_fit(&v);
    printf("Capacity of vector v after shrink : %d\n", v.capacity);
    printf("\n");

    printf("Vector a : ");
    vector_print(&a);
    printf("Size of vector a : %d\n", a.size);
    printf("input 3 : %f\n", at(&a, 3));
    printf("input 7 : %f\n", at(&a, 7));
    printf("input -2 : %f\n", at(&a, -2));
    return 0;
}