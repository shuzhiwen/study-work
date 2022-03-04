#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

enum Status vector_init(struct Vector *vec, int cap) {
    if (cap <= 0) {
        return STATUS_ERR_INVALID_CAPACITY;
    }

    vec->buffer = (DataType *)malloc(cap * sizeof(DataType));
    if (vec->buffer == NULL) {
        return STATUS_ERR_ALLOC;
    }

    vec->capacity = cap;
    vec->size = 0;

    return STATUS_OK;
}

enum Status vector_reserve(struct Vector *vec, int new_cap) {
    if (new_cap < vec->size) {
        return STATUS_ERR_INVALID_CAPACITY;
    }

    DataType *p = (DataType *)realloc(vec->buffer, new_cap * sizeof(DataType));
    if (p == NULL) {
        return STATUS_ERR_ALLOC;
    }

    vec->buffer = p;
    vec->capacity = new_cap;

    return STATUS_OK;
}

void vector_destroy(struct Vector *vec) {
    if (vec->buffer == NULL) {
        return;
    }

    free(vec->buffer);
    vec->buffer = NULL;
    vec->capacity = 0;
    vec->size = 0;
}

enum Status vector_insert(struct Vector *vec, int pos, DataType value) {
    int i;
    enum Status err;

    if (pos < 0 || pos > vec->size) {
        return STATUS_ERR_INVALID_RANGE;
    }

    if (vec->size == vec->capacity) {
        err = vector_reserve(vec, 2 * vec->capacity);
        if (err != STATUS_OK) {
            return err;
        }
    }

    for (i = vec->size - 1; i >= pos; i--) {
        vec->buffer[i + 1] = vec->buffer[i];
    }

    vec->buffer[pos] = value;
    vec->size++;

    return STATUS_OK;
}

enum Status vector_push_back(struct Vector *vec, DataType value) {
    return vector_insert(vec, vec->size, value);
}

enum Status vector_push_front(struct Vector *vec, DataType value) {
    return vector_insert(vec, 0, value);
}

enum Status vector_remove_at(struct Vector *vec, int pos) {
    int i;

    if (pos < 0 || pos > vec->size - 1) {
        return STATUS_ERR_INVALID_RANGE;
    }

    for (i = pos + 1; i < vec->size; i++) {
        vec->buffer[i - 1] = vec->buffer[i];
    }

    vec->size--;

    return STATUS_OK;
}

enum Status vector_pop_front(struct Vector *vec) { return vector_remove_at(vec, 0); }

enum Status vector_pop_back(struct Vector *vec) { return vector_remove_at(vec, vec->size - 1); }

DataType vector_at(struct Vector *vec, int index) {
    int r = index % vec->size;
    if (r < 0) r += vec->size;

    return vec->buffer[r];
}
