#include "queue.h"

enum Status queue_init(Queue *queue, int n) { return vector_init(queue, n); }

enum Status queue_enqueue(Queue *queue, DataType data) { return vector_push_back(queue, data); }

DataType queue_dequeue(Queue *queue) {
    DataType x = vector_at(queue, 0);
    vector_pop_front(queue);

    return x;
}

int queue_size(Queue *queue) { return queue->size; }

void queue_destroy(Queue *queue) { vector_destroy(queue); }