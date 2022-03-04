#pragma once

#include "common.h"
#include "list.h"
#include "vector.h"

struct trietree {
    int freq;
    char data[50];
    struct List l;
    struct trietree *next[26];
};

void trietree_free(struct trietree *root);

struct trietree *trietree_build_stat(struct Vector *vec);

struct trietree *trietree_find(struct trietree *root, char *s);