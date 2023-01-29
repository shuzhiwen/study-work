#include "sorted_list.h"

#include <stdio.h>

struct ListNode *find_fit_location(struct List *dst, struct ListNode *node) {
    struct ListNode *p = dst->head;

    while (p->next && p->next->data < node->data) {
        p = p->next;
    }

    if (p->data > node->data) {
        return NULL;
    }

    return p;
}

// TODO:
enum Status merge_sorted_lists(struct List *dst, struct List *src1,
                               struct List *src2) {  // 复杂度O(m+n)
    struct ListNode *p1 = src1->head, *p2 = src2->head;

    while (p1 != NULL || p2 != NULL) {
        if (p1 == NULL && p2 != NULL) {  // src1为空但src2还未移动完
            if (dst->head == NULL) {     // 特殊情况：当且仅当src１传入空指针
                dst->head = dst->tail = p2;
                p2 = p2->next;
            }

            while (p2) {
                dst->tail->next = p2;
                dst->tail = p2;
                dst->size++;
                p2 = p2->next;
            }
            break;
        } else if (p2 == NULL && p1 != NULL) {  // src2为空但src1还未移动完
            if (dst->head == NULL) {            // 特殊情况：当且仅当src2传入空指针
                dst->head = dst->tail = p1;
                p1 = p1->next;
            }

            while (p1) {
                dst->tail->next = p1;
                dst->tail = p1;
                dst->size++;
                p1 = p1->next;
            }
            break;
        }

        if (p1->data < p2->data) {
            if (dst->head == NULL) {  // 待插入的链表为空
                dst->head = dst->tail = p1;
            } else {
                dst->tail->next = p1;
                dst->tail = p1;
            }

            dst->size++;
            p1 = p1->next;

        } else {
            if (dst->head == NULL) {  // 待插入的链表为空
                dst->head = dst->tail = p2;
            } else {
                dst->tail->next = p2;
                dst->tail = p2;
            }

            dst->size++;
            p2 = p2->next;
        }

        dst->tail->next = NULL;
    }

    return STATUS_OK;
}

// TODO:
enum Status merge_multiple_lists(struct List *dst, struct List **srcs,
                                 int n) {  // 插入排序，适用于三个以上的链表
    if (srcs == NULL) {
        return STATUS_ERR_NULL_LIST;
    } else {
        merge_sorted_lists(dst, *srcs, (*srcs) + 1);
    }

    for (int i = 2; i < n; i++) {
        struct ListNode *p = ((*srcs) + i)->head;

        while (p != NULL) {
            struct ListNode *s = find_fit_location(dst, p), *q = p->next;

            if (s == NULL) {  // 头部插入
                p->next = dst->head;
                dst->head = p;
            } else if (s->next == NULL) {  // 尾部插入
                dst->tail->next = p;
                dst->tail = p;
                dst->tail->next = NULL;
            } else {  // 中部插入
                p->next = s->next;
                s->next = p;
            }

            p = q;
            dst->size++;
        }
    }

    return STATUS_OK;
}