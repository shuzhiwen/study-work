#include "trietree.h"

//释放字典树以及依赖于字典树的内存空间
void trietree_free(struct trietree *root) {
    for (int i = 0; i < 26; i++) {
        if (root != NULL && root->next[i] != NULL) {
            trietree_free(root->next[i]);
        }
    }

    if (root->l.size != 0) {
        list_destroy(&root->l);
    }

    if (root != NULL) {
        free(root);
    }
}

//根据站点拼音查找其是否在字典树中，如是则返回其地址，否则返回NULL
struct trietree *trietree_find(struct trietree *root, char *s) {
    int len = strlen(s);
    struct trietree *p = root;

    if (strcmp(s, "?????") == 0) {
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        if (i == len - 1 && p->next[s[i] - 'a'] != NULL &&
            strcmp(p->next[s[i] - 'a']->data, s) == 0) {
            return p->next[s[i] - 'a'];
        }

        if (p->next[s[i] - 'a'] != NULL) {
            p = p->next[s[i] - 'a'];
        } else {
            return NULL;
        }
    }

    return NULL;
}

//辅助函数，建立字典树中单个结点
void trietree_build_node(struct trietree **root, char *s) {
    struct trietree *T = (struct trietree *)malloc(sizeof(struct trietree));

    strcpy(T->data, s);
    for (int i = 0; i < 26; i++) {
        T->next[i] = NULL;
    }

    T->freq = 0;
    list_init(&T->l);
    if (*root == NULL) {
        *root = T;
    } else {
        (*root)->next[s[0] - 'a'] = T;
    }
}

//根据数组vec构建字典树
struct trietree *trietree_build_stat(struct Vector *vec) {
    struct trietree *root = NULL;
    char eng[20];

    trietree_build_node(&root, "?????");
    for (int i = 0; i < vec->size; i++) {
        strcpy(eng, vector_at(vec, i)->eng_name);

        struct trietree *p = root;
        int len = strlen(eng);

        for (int i = 0; i < len; i++) {
            if (i == len - 1) {
                if (p->next[eng[i] - 'a'] == NULL) {
                    trietree_build_node(&p->next[eng[i] - 'a'], eng);
                } else {
                    strcpy(p->next[eng[i] - 'a']->data, eng);
                }
            } else if (p->next[eng[i] - 'a'] == NULL) {
                trietree_build_node(&p->next[eng[i] - 'a'], "?????");
            }

            p = p->next[eng[i] - 'a'];
        }
    }

    return root;
}