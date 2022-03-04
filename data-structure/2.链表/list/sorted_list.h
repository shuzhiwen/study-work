#include "list.h"

#ifndef SORTED_LIST_H
#define SORTED_LIST_H

// Merge sorted list src1 and src2 to dst
// src1和src2是从小到大排好序的链表，将它们所有节点移到dst中，并按照从小到大的顺序排列
enum Status merge_sorted_lists(struct List *dst, struct List *src1, struct List *src2);

// Merge k lists
// srcs是n个从小到大排好序的链表，将它们所有节点移到dst中，并按照从小到大的顺序排列
enum Status merge_multiple_lists(struct List *dst, struct List **srcs, int n);

// 辅助函数，找到待插入节点在目标有序链表中合适的的地址
struct ListNode *find_fit_location(struct List *dst, struct ListNode *node);

#endif  // SORTED_LIST_H