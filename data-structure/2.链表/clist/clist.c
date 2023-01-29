#include "clist.h"

#include <stdio.h>
#include <stdlib.h>

void clist_init(struct CList *list) {
    list->size = 0;
    list->head = NULL;
}

void clist_destroy(struct CList *list) {
    while (clist_size(list) > 0) {
        clist_remove_after(list, list->head);
    }
}

// TODO:
enum Status clist_insert_after(struct CList *list, struct CListNode *node, DataType data) {
    struct CListNode *new_node = (struct CListNode *)malloc(sizeof(struct CListNode));

    if (new_node == NULL) {
        return STATUS_ERR_ALLOC;
    }

    new_node->data = data;

    if (node == NULL) {
        // Insertion at the head of the list
        if (list->head == NULL) {  // 链表为空
            list->head = new_node;
            new_node->next = new_node;
        } else {  // 插入成为头节点
            struct CListNode *p = list->head;

            while (p->next != list->head) {  // 使得ｐ节点成为ｈｅａｄ节点的上一个节点
                p = p->next;
            }

            p->next = new_node;
            new_node->next = list->head;
            list->head = new_node;
        }
    } else {
        // Insertion at somewhere other than at the head
        new_node->next = node->next;
        node->next = new_node;
    }

    list->size++;

    return STATUS_OK;
}

// TODO:
enum Status clist_remove_after(struct CList *list, struct CListNode *node) {
    struct CListNode *old_node;
    // Empty list
    if (clist_size(list) == 0) {
        return STATUS_ERR_INVALID_RANGE;
    }

    if (list->head->next == list->head) {  // 只有一个节点
        old_node = list->head;
        clist_init(list);
    } else {
        if (node == NULL) {
            // Remove from the head of the list
            struct CListNode *p = list->head;

            while (p->next != list->head) {  // 使得ｐ节点成为ｈｅａｄ节点的上一个节点
                p = p->next;
            }

            old_node = list->head;
            p->next = list->head->next;
        } else {
            // Remove from somewhere other than the head
            old_node = node->next;
            node->next = node->next->next;
        }

        free(old_node);
        list->size--;
    }

    return STATUS_OK;
}

// Get list size
int clist_size(struct CList *list) { return list->size; }