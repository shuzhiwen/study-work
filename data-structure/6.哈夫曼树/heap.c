#include "heap.h"

void heap_swap(DataType *a, DataType *b) {
    DataType tmp = *a;
    *a = *b;
    *b = tmp;

    /*(*b)->left = (*a)->left;
    (*b)->right = (*a)->right;

    if (flag == 0) {
      (*a)->left = *b;
      (*a)->right = tmp->right;
    } else if (flag == 1){
      (*a)->right = *b;
      (*a)->left = tmp->left;
    } else {
      (*a)->left = tmp->left;
      (*a)->right = tmp->right;
    }*/
}

enum Status heap_init(Heap *h) {
    enum Status st = vector_init(h, 10);
    // Index 0 is not used
    h->size = 1;
    return st;
}

void heap_rebuild(Heap *h) {
    int n = heap_size(h);

    for (int i = n / 2; i > 0; i--) {
        heap_adjust(h, i);
    }
}

int heap_size(Heap *h) { return h->size - 1; }

void heap_adjust(Heap *h, int node) {
    int n = heap_size(h);

    if (node > n / 2) {
        // node has no children
        return;
    }

    // Choose smaller child
    int left = 2 * node;
    int right = 2 * node + 1;
    int small =
        (right <= n && h->buffer[right]->frequency < h->buffer[left]->frequency ? right : left);

    // Swap
    if (h->buffer[node]->frequency > h->buffer[small]->frequency) {
        heap_swap(&h->buffer[node], &h->buffer[small]);
        heap_adjust(h, small);
    }
}

DataType heap_pop(Heap *h) {
    // Put last node to heap top
    int n = heap_size(h), tmp;

    heap_swap(&h->buffer[1], &h->buffer[n]);
    h->size--;

    // Adjust heap
    heap_adjust(h, 1);

    return h->buffer[n];
}

DataType heap_top(Heap *h) { return h->buffer[1]; }
