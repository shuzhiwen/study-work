#pragma once

#include "common.h"

struct FileTree {
    bool isDirectory;   //类型标识
    char name[20];      //文件夹或文件的名称
    struct File *file;  //文件地址，如是目录则为NULL
    struct List *children;
};

typedef struct FileTree List_DataType;

struct ListNode {
    List_DataType data;
    struct ListNode *next;
};

struct List {
    int size;
    struct ListNode *head;
    struct ListNode *tail;
};

// Init a list
void list_init(struct List *list);
// Destroy a list
void list_destroy(struct List *list);

// Insert `data` after node `node`
enum Status list_insert_after(struct List *list, struct ListNode *node, List_DataType data);
// Insert `data` at front of `list`
enum Status list_push_front(struct List *list, List_DataType data);
enum Status list_push_back(struct List *list, List_DataType data);

// Remove the node after `node`
enum Status list_remove_after(struct List *list, struct ListNode *node);
// Remove the first node
enum Status list_pop_front(struct List *list);

// Get list size
int list_size(struct List *list);
// Get i-th element
struct ListNode *list_at(struct List *list, int i);
// Get node before `node`
struct ListNode *list_prev(struct List *list, struct ListNode *node);