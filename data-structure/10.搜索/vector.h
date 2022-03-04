#pragma once

#include "common.h"
#include "student.h"

typedef struct Student DataType;

struct Vector {
    int capacity;
    int size;
    DataType *buffer;
};

/* Allocate and destroy buffer for vector */
enum Status vector_init(struct Vector *vec, int cap);
void vector_destroy(struct Vector *vec);
enum Status vector_reserve(struct Vector *vec, int new_cap);

/* Insert element */
enum Status vector_insert(struct Vector *vec, int pos, DataType value);
enum Status vector_push_back(struct Vector *vec, DataType value);
enum Status vector_push_front(struct Vector *vec, DataType value);

/* Delete element */
enum Status vector_remove_at(struct Vector *vec, int pos);
enum Status vector_pop_front(struct Vector *vec);
enum Status vector_pop_back(struct Vector *vec);

DataType vector_at(struct Vector *vec, int index);
