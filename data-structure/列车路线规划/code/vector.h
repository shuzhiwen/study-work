#pragma once

#include "common.h"

typedef struct station Vec_DataType;

struct Vector {
    int capacity;
    int size;
    Vec_DataType *buffer;
};

/* Allocate and destroy buffer for vector */
enum Status vector_init(struct Vector *vec, int cap);
void vector_destroy(struct Vector *vec);
enum Status vector_reserve(struct Vector *vec, int new_cap);

/* Insert element */
enum Status vector_insert(struct Vector *vec, int pos, Vec_DataType value);
enum Status vector_push_back(struct Vector *vec, Vec_DataType value);
enum Status vector_push_front(struct Vector *vec, Vec_DataType value);

/* Find element */
int vector_find_first(struct Vector *vec, Vec_DataType value);
int vector_find_next(struct Vector *vec, Vec_DataType value, int start_pos);

/* Delete element */
enum Status vector_remove_at(struct Vector *vec, int pos);
enum Status vector_pop_front(struct Vector *vec);
enum Status vector_pop_back(struct Vector *vec);
void vector_delete_value(struct Vector *vec, Vec_DataType value);

/* Methods to be implemented */
void vector_reverse(struct Vector *vec);
void vector_swap(struct Vector *a, struct Vector *b);
enum Status vector_shrink_to_fit(struct Vector *vec);
Vec_DataType *vector_at(struct Vector *vec, int index);
