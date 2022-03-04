#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

int vector_is_NULL(struct vector *vec) { return vec == NULL; }

int vector_realloc(struct vector *vec) {
    datatype *p = (datatype *)realloc(vec->data, vec->capacity * 2 * sizeof(datatype));
    if (p == NULL) {
        printf("Reallocate failed!\n");
        return -1;
    }

    vec->data = p;
    vec->capacity *= 2;

    return 0;
}

int vector_new(struct vector *vec, int cap) {
    if (cap <= 0) {
        printf("Wrong capacity!\n");
        return -1;
    }

    vec->data = (datatype *)malloc(cap * sizeof(datatype));
    if (vec->data == NULL) {
        printf("Allocate vector failed!\n");
        return -1;
    }

    vec->capacity = cap;
    vec->size = 0;

    return 0;
}

int vector_destory(struct vector *vec) {
    if (vec->data != NULL) {
        free(vec->data);
        vec->data = NULL;
        vec->capacity = 0;
        vec->size = 0;
    }

    return 0;
}

int vector_print(struct vector *vec) {
    int i;

    if (vector_is_NULL(vec)) {
        printf("Print NULL vector\n");
        return -1;
    }

    for (i = 0; i < vec->size; i++) {
        printf("%f ", vec->data[i]);
    }
    printf("\n");

    return 0;
}

int vector_insert(struct vector *vec, int pos, datatype value) {
    int i;

    if (pos < 0 || pos > vec->size) {
        printf("Wrong insert position!\n");
        return -1;
    }

    if (vec->size == vec->capacity) {
        vector_realloc(vec);
    }

    for (i = vec->size - 1; i >= pos; i--) {
        vec->data[i + 1] = vec->data[i];
    }

    vec->data[pos] = value;
    vec->size++;

    return 0;
}

int vector_push_back(struct vector *vec, datatype value) {
    if (vector_insert(vec, vec->size, value) != 0) {
        printf("Vector_push_back failed!\n");
        return -1;
    }

    return 0;
}

int vector_push_front(struct vector *vec, datatype value) {
    if (vector_insert(vec, 0, value) != 0) {
        printf("Vector_push_front failed!");
        return -1;
    }

    return 0;
}

int vector_remove_at(struct vector *vec, int pos) {
    int i;

    if (vector_is_NULL(vec)) {
        printf("Vector is NULL\n");
        return -1;
    }

    if (pos < 0 || pos > vec->size - 1) {
        printf("Delete at wrong position!\n");
        return -1;
    }

    for (i = pos + 1; i < vec->size; i++) {
        vec->data[i - 1] = vec->data[i];
    }

    vec->size--;

    return 0;
}

int vector_pop_front(struct vector *vec) {
    if (vector_remove_at(vec, 0) != 0) {
        printf("Vector_pop_front failed!");
        return -1;
    }

    return 0;
}

int vector_pop_back(struct vector *vec) {
    if (vector_remove_at(vec, vec->size - 1) != 0) {
        printf("Vector_pop_back failed!");
        return -1;
    }

    return 0;
}

int vector_delete_value(struct vector *vec, datatype value) {
    int pos = 0;

    if (vector_is_NULL(vec)) {
        printf("Vector is NULL\n");
        return -1;
    }

    while ((pos = vector_find_next(vec, value, pos)) != -1) {
        vector_remove_at(vec, pos);
    }

    return 0;
}

int vector_find_next(struct vector *vec, datatype value, int start_pos) {
    int i;

    if (vector_is_NULL(vec)) {
        printf("Vector is NULL\n");
        return -1;
    }

    if (vec->size == 0) {
        return -1;
    }

    if (start_pos < 0 || start_pos >= vec->size) {
        printf("Invalid start position!\n");
        return -1;
    }

    for (i = start_pos; i < vec->size; i++) {
        if (vec->data[i] == value) {
            return i;
        }
    }

    return -1;
}

int vector_find_first(struct vector *vec, datatype value) {
    return vector_find_next(vec, value, 0);
}

int vector_union(struct vector *c, struct vector *a, struct vector *b) {
    int i;

    if (vector_is_NULL(a) || vector_is_NULL(b)) {
        printf("Vector is NULL\n");
        return -1;
    }

    for (i = 0; i < a->size; i++) {
        if (vector_find_first(c, a->data[i]) == -1) {
            vector_push_back(c, a->data[i]);
        }
    }

    for (i = 0; i < b->size; i++) {
        if (vector_find_first(c, b->data[i]) == -1) {
            vector_push_back(c, b->data[i]);
        }
    }

    return 0;
}

int vector_reverse(struct vector *vec) {
    int i;
    datatype n;

    if (vector_is_NULL(vec)) {
        printf("Vector is NULL\n");
        return -1;
    }

    for (i = 0; i < vec->size / 2; i++) {
        n = vec->data[i];
        vec->data[i] = vec->data[vec->size - i - 1];
        vec->data[vec->size - i - 1] = n;
    }

    return 0;
}

int vector_swap(struct vector *a, struct vector *b) {
    int i, asize = a->size, bsize = b->size;

    if (vector_is_NULL(a) || vector_is_NULL(b)) {
        printf("Vector is NULL\n");
        return -1;
    }

    for (i = 0; i < asize; i++) {
        vector_push_back(b, a->data[i]);
    }

    for (i = 0; i < bsize; i++) {
        vector_push_back(a, b->data[i]);
    }

    for (i = 0; i < bsize; i++) {
        a->data[i] = a->data[asize + i];
    }

    for (i = 0; i < asize; i++) {
        b->data[i] = b->data[bsize + i];
    }

    b->size = asize;
    a->size = bsize;

    return 0;
}

int vector_shrink_to_fit(struct vector *vec) {
    datatype *p = (datatype *)realloc(vec->data, vec->size * sizeof(datatype));
    if (p == NULL) {
        printf("Reallocate failed!\n");
        return -1;
    }

    vec->data = p;
    vec->capacity = vec->size;

    return 0;
}

datatype at(struct vector *vec, int index) {
    if (vector_is_NULL(vec)) {
        printf("Vector is NULL\n");
        return -1;
    }

    while (index < 0) {
        index += vec->size;
    }

    index = index % vec->size;

    return vec->data[index];
}
