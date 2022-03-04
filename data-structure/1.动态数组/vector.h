#ifndef DS_VECTOR_H_
#define DS_VECTOR_H_

typedef double datatype;

struct vector {
    int capacity;
    int size;
    datatype *data;
};

int vector_is_NULL(struct vector *vec);

int vector_new(struct vector *vec, int cap);

int vector_destory(struct vector *vec);

int vector_print(struct vector *vec);

int vector_insert(struct vector *vec, int pos, datatype value);

int vector_push_back(struct vector *vec, datatype value);

int vector_push_front(struct vector *vec, datatype value);

int vector_remove_at(struct vector *vec, int pos);

int vector_pop_front(struct vector *vec);

int vector_pop_back(struct vector *vec);

int vector_find_first(struct vector *vec, datatype value);

int vector_find_next(struct vector *vec, datatype value, int start_pos);

int vector_delete_value(struct vector *vec, datatype value);

int vector_union(struct vector *c, struct vector *a, struct vector *b);

int vector_reverse(struct vector *vec);

int vector_swap(struct vector *a, struct vector *b);

int vector_shrink_to_fit(struct vector *vec);

datatype at(struct vector *vec, int index);

#endif /* DS_VECTOR_H_ */