#include "dlist.h"

#include <stdio.h>
#include <stdlib.h>

void dlist_init(struct DList *list) {
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void dlist_destroy(struct DList *list) {
    while (dlist_size(list) > 0) {
        dlist_remove(list, list->tail);
    }

    dlist_init(list);
}

// TODO:
enum Status dlist_insert_after(struct DList *list, struct DListNode *node, DataType data) {
    struct DListNode *new_node = (struct DListNode *)malloc(sizeof(struct DListNode));

    if (new_node == NULL) {
        return STATUS_ERR_ALLOC;
    }

    new_node->data = data;

    if (node == NULL) {
        if (dlist_size(list) == 0) {  // 待插入链表为空
            list->tail = list->head = new_node;
            new_node->prev = new_node->next = NULL;
        } else {  // 头部插入
            new_node->next = list->head;
            new_node->prev = NULL;
            list->head->prev = new_node;
            list->head = new_node;
        }

    } else {
        if (node->next == NULL) {  // 尾部插入
            node->next = new_node;
            new_node->prev = node;
            new_node->next = NULL;
            list->tail = new_node;
        } else {  // 中部插入
            new_node->next = node->next;
            new_node->prev = node;
            node->next->prev = new_node;
            node->next = new_node;
        }
    }

    list->size++;
    return STATUS_OK;
}

// TODO:
enum Status dlist_insert_before(struct DList *list, struct DListNode *node, DataType data) {
    struct DListNode *new_node = (struct DListNode *)malloc(sizeof(struct DListNode));

    if (new_node == NULL) {
        return STATUS_ERR_ALLOC;
    }

    new_node->data = data;

    if (node == NULL) {
        if (dlist_size(list) == 0) {  // 待插入链表为空
            list->tail = list->head = new_node;
            new_node->prev = new_node->next = NULL;
        } else {  // 尾部插入
            node->next = new_node;
            new_node->prev = node;
            new_node->next = NULL;
            list->tail = new_node;
        }

    } else {
        if (node->prev == NULL) {  // 头部插入
            new_node->next = list->head;
            new_node->prev = NULL;
            list->head->prev = new_node;
            list->head = new_node;
        } else {  // 中部插入
            new_node->prev = node->prev;
            new_node->next = node;
            node->prev->next = new_node;
            node->prev = new_node;
        }
    }

    list->size++;

    return STATUS_OK;
}

enum Status dlist_push_front(struct DList *list, DataType data) {
    return dlist_insert_before(list, list->head, data);
}

enum Status dlist_push_back(struct DList *list, DataType data) {
    return dlist_insert_after(list, list->tail, data);
}

// TODO:
enum Status dlist_remove(struct DList *list, struct DListNode *node) {
    // Empty list
    if (dlist_size(list) == 0) {
        return STATUS_ERR_INVALID_RANGE;
    }

    if (node->prev == NULL && node->next == NULL) {  // 只有一个元素
        dlist_init(list);
    } else if (node->prev == NULL) {  // 头部删除
        node->next->prev = NULL;
        list->head = list->head->next;
    } else if (node->next == NULL) {  // 尾部删除
        node->prev->next = NULL;
        list->tail = list->tail->prev;
    } else {  // 中部删除
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    free(node);
    list->size--;

    return STATUS_OK;
}

enum Status dlist_pop_front(struct DList *list) { return dlist_remove(list, list->head); }

enum Status dlist_pop_back(struct DList *list) { return dlist_remove(list, list->tail); }

int dlist_size(struct DList *list) { return list->size; }