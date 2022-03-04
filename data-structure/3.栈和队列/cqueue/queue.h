#include "vector.h"

#ifndef LIST_H
#define LIST_H

typedef struct Vector Queue;

enum Status queue_init(Queue *queue, int n);

enum Status queue_enqueue(Queue *queue, DataType data);

DataType queue_dequeue(Queue *queue);

int queue_size(Queue *queue);

void queue_destroy(Queue *queue);

#endif  // LIST_H
