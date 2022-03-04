#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculate_frequency(int a[256], char *s) {
    memset(a, 0, sizeof(int) * 256);

    for (int i = 0; s[i] != 0; i++) {
        a[s[i]]++;
    }
}

void build_treenode(struct Vector *vec, int a[]) {
    for (int i = 0; i < 256; i++) {
        if (a[i] != 0) {
            struct BTree *root = malloc(sizeof(struct BTree));

            root->data = i;
            root->frequency = a[i];
            root->left = root->right = NULL;
            vector_push_back(vec, root);
        }
    }
}

DataType pop_smallest(struct Vector *vec) {
    DataType min_node = vec->buffer[0];
    int index = 0, value = min_node->frequency;

    for (int i = 0; i < vec->size; i++) {
        if (vec->buffer[i]->frequency < value) {
            value = vec->buffer[i]->frequency;
            min_node = vec->buffer[i];
            index = i;
        }
    }

    vector_remove_at(vec, index);
    return min_node;
}

// TODO:
// 用数组构建一个 Huffman 树
struct BTree *huffman_build_using_array(char *s) {
    struct Vector v;
    int a[256];

    vector_init(&v, 10);
    calculate_frequency(a, s);
    build_treenode(&v, a);

    while (v.size != 1) {
        DataType m1, m2;

        m1 = pop_smallest(&v);
        m2 = pop_smallest(&v);

        DataType newnode = malloc(sizeof(struct BTree));
        newnode->frequency = m1->frequency + m2->frequency;
        newnode->data = -1;
        newnode->left = m1;
        newnode->right = m2;
        vector_push_back(&v, newnode);
    }

    return v.buffer[0];
}

// TODO:
// 使用堆构建一个 Huffman 树
struct BTree *huffman_build_using_heap(char *s) {
    Heap h;
    int a[256];

    heap_init(&h);
    calculate_frequency(a, s);
    build_treenode(&h, a);
    heap_rebuild(&h);

    while (h.size != 2) {
        DataType m1, m2;

        m1 = heap_pop(&h);
        m2 = heap_pop(&h);

        DataType newnode = malloc(sizeof(struct BTree));
        newnode->frequency = m1->frequency + m2->frequency;
        newnode->data = -1;
        newnode->left = m1;
        newnode->right = m2;
        vector_push_back(&h, newnode);
        heap_rebuild(&h);
    }

    return heap_top(&h);
}

int Isleaf(struct BTree *root) { return root != NULL && root->left == NULL && root->right == NULL; }

//往左为0，往右为1
int coding_count(struct BTree *root, int a[], char s, int index) {
    int flag = 0;

    if (Isleaf(root)) {
        if (root->data == s) {
            return 1;
        } else {
            a[index] = -1;
            return 0;
        }
    }

    if (!flag) {
        a[index] = 0;
        flag = coding_count(root->left, a, s, index + 1);
    }
    if (!flag) {
        a[index] = 1;
        flag = coding_count(root->right, a, s, index + 1);
    }

    if (flag == 0) {
        a[index] = -1;
    }
    return flag;
}

//哈弗曼树编码查询并返回长度
int coding_refer(struct BTree *root, char s) {
    int a[256], i;

    memset(a, -1, sizeof(a));
    coding_count(root, a, s, 0);

    for (i = 0; a[i] != -1; i++) {
        printf("%d", a[i]);
    }

    return i;
}

// TODO:
// 用 Huffman 树ht对字符串 s
// 进行编码，打印出编码结果（0、1字符串），并返回编码后的长度
int huffman_encode(struct BTree *ht, char *s) {
    int count = 0;

    for (int i = 0; s[i] != 0; i++) {
        count += coding_refer(ht, s[i]);
    }

    printf("\n");
    return count;
}

// TODO:
// 用 Huffman 树 ht 对字符串 s
// （由0、1组成）进行解码，打印出解码结果，并返回解码后的长度
int huffman_decode(struct BTree *ht, char *s) {
    int i = 0, count = 0;

    while (s[i] != 0) {
        struct BTree *p = ht;

        while (!Isleaf(p)) {
            if (s[i] == '0') {
                p = p->left;
            } else {
                p = p->right;
            }
            i++;
        }

        printf("%c", p->data);
        count++;
    }

    printf("\n");
    return count;
}
