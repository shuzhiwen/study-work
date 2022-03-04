#include "btree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BTree *btree_create(char root, struct BTree *left, struct BTree *right) {
    struct BTree *root_node = malloc(sizeof(struct BTree));
    root_node->data = root;
    root_node->left = left;
    root_node->right = right;

    return root_node;
}

void btree_destroy(struct BTree *root) {
    if (root == NULL) {
        return;
    }

    btree_destroy(root->left);
    btree_destroy(root->right);
    free(root);
}

struct BTree *btree_from_pre_mid(char *pre, char *mid, int len) {
    if (len == 0) {
        return NULL;
    }

    char *root = strchr(mid, pre[0]);
    if (root == NULL) {
        return NULL;
    }

    int ll = root - mid;
    struct BTree *left = btree_from_pre_mid(pre + 1, mid, ll);
    struct BTree *right = btree_from_pre_mid(pre + ll + 1, root + 1, len - ll - 1);

    return btree_create(*root, left, right);
}

// TODO:
// 根据后序`post`和中序`mid`遍历构建一棵二叉树
struct BTree *btree_from_post_mid(char *post, char *mid, int len) {
    if (len == 0) {
        return NULL;
    }

    char *root = strchr(mid, post[len - 1]);
    if (root == NULL) {
        return NULL;
    }

    int ll = root - mid;
    struct BTree *left = btree_from_post_mid(post, mid, ll);
    struct BTree *right = btree_from_post_mid(post + ll, root + 1, len - ll - 1);

    return btree_create(*root, left, right);
}

// TODO:
// 根据层次`level`和中序`mid`遍历构建一棵二叉树
struct BTree *btree_from_level_mid(char *level, char *mid, int len) {
    if (len == 0) {
        return NULL;
    }

    char *root = strchr(mid, level[0]);
    if (root == NULL) {
        return NULL;
    }

    int ll = root - mid, count, j, k;
    char *sl = malloc(sizeof(char) * ll);
    char *sr = malloc(sizeof(char) * (len - ll));

    count = 0;
    for (j = 1; j < len; j++) {
        for (int k = 0; k < ll; k++) {
            if (level[j] == mid[k]) {
                sl[count++] = level[j];
                break;
            }
        }
    }

    count = 0;
    for (j = 1; j < len; j++) {
        for (k = 0; k < ll; k++) {
            if (level[j] == mid[k]) {
                break;
            }
        }
        if (k == ll) {
            sr[count++] = level[j];
        }
    }

    struct BTree *left = btree_from_level_mid(sl, mid, ll);
    struct BTree *right = btree_from_level_mid(sr, root + 1, len - ll - 1);

    return btree_create(*root, left, right);
}

// TODO:
// 根据字符串`s`构建一棵搜索二叉树
struct BTree *btree_build_search_tree(char *s) {
    struct BTree *root = btree_create(s[0], NULL, NULL);

    for (int i = 1; i < strlen(s); i++) {
        struct BTree *p = root, *q = NULL;
        int flag = 0;  //标记当前节点是其父节点的左子树还是右子树

        while (1) {
            if (p != NULL) {
                q = p;
            }

            if (p == NULL || p->data == s[i]) {
                break;
            } else if (s[i] > p->data) {
                p = p->right;
                flag = 1;
            } else if (s[i] < p->data) {
                p = p->left;
                flag = 0;
            }
        }

        if (p == NULL) {
            p = malloc(sizeof(struct BTree));
            p->data = s[i];
            p->left = p->right = NULL;
            if (q == NULL) {
                continue;
            } else if (flag == 1) {
                q->right = p;
            } else {
                q->left = p;
            }
        }
    }

    return root;
}

// TODO:
// 在二叉搜索树`root`中查找`value`，如果找到返回相应节点，否则返回NULL
struct BTree *btree_find(struct BTree *root, char value) {
    if (root == NULL) {
        return NULL;
    } else if (root->data == value) {
        return root;
    } else if (root->data > value) {
        return btree_find(root->left, value);
    } else {
        return btree_find(root->right, value);
    }
}

void btree_pre_order(struct BTree *root) {
    if (root == NULL) {
        return;
    }

    putchar(root->data);
    btree_pre_order(root->left);
    btree_pre_order(root->right);
}

void btree_mid_order(struct BTree *root) {
    if (root == NULL) {
        return;
    }

    btree_mid_order(root->left);
    putchar(root->data);
    btree_mid_order(root->right);
}

void btree_post_order(struct BTree *root) {
    if (root == NULL) {
        return;
    }

    btree_post_order(root->left);
    btree_post_order(root->right);
    putchar(root->data);
}

// 辅助函数
struct BTree *btree_find_value(struct BTree *root, char value) {
    if (root == NULL) {
        return NULL;
    } else if (root->data == value) {
        return root;
    } else {
        struct BTree *p = btree_find_value(root->left, value);
        struct BTree *q = btree_find_value(root->right, value);

        if (p != NULL) {
            return p;
        } else if (q != NULL) {
            return q;
        } else {
            return NULL;
        }
    }
}

// TODO:
// 对二叉树进行层次遍历
void btree_level_order(struct BTree *root) {
    Queue q;

    queue_init(&q);
    queue_enqueue(&q, root->data);
    while (!queue_empty(&q)) {
        char data = queue_dequeue(&q);
        struct BTree *p = btree_find_value(root, data);

        putchar(data);
        if (p->left != NULL) {
            queue_enqueue(&q, p->left->data);
        }
        if (p->right != NULL) {
            queue_enqueue(&q, p->right->data);
        }
    }
}

int max(int a, int b) { return a > b ? a : b; }

int btree_depth(struct BTree *root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + max(btree_depth(root->left), btree_depth(root->right));
}

int btree_leaves(struct BTree *root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    return btree_leaves(root->left) + btree_leaves(root->right);
}

void btree_flip(struct BTree *root) {
    if (root == NULL) {
        return;
    }

    struct BTree *tmp = root->left;
    root->left = root->right;
    root->right = tmp;

    btree_flip(root->left);
    btree_flip(root->right);
}

// TODO:
// 判断两棵树是否相同, 相同返回1， 不同返回0
int btree_is_same(struct BTree *a, struct BTree *b) {
    int flag = 0;

    if (a == NULL && b == NULL) {
        return 1;
    } else if (a == NULL && b != NULL || a != NULL && b == NULL) {
        return 0;
    } else {
        flag += btree_is_same(a->left, b->left) + btree_is_same(a->right, b->right);
        if (a->data != b->data) {
            flag = 0;
        }
    }

    return flag == 2 ? 1 : 0;
}

// TODO:
// 判断两棵树是否同构，即能够通过若干次左右子树的交换由a变为b，同构返回1，不同构返回2
int btree_is_isomorphic(struct BTree *a, struct BTree *b) {
    int flag = 0;

    if (a == NULL && b == NULL) {
        return 1;
    } else if (a == NULL && b != NULL || a != NULL && b == NULL) {
        return 2;
    }

    if (a->data != b->data) {
        return 2;
    } else {
        if (a->left != NULL && b->left != NULL && a->right != NULL && b->right != NULL) {
            if (a->left->data == b->left->data && a->right->data == b->right->data) {
                flag += btree_is_same(a->left, b->left) + btree_is_same(a->right, b->right);
            }
            if (a->left->data == b->right->data && a->right->data == b->left->data) {
                flag += btree_is_same(a->left, b->right) + btree_is_same(a->right, b->left);
            }
        } else if (a->left == NULL && b->left == NULL && a->right != NULL && b->right != NULL ||
                   a->left != NULL && b->left != NULL && a->right == NULL && b->right == NULL) {
            flag += btree_is_same(a->left, b->left) + btree_is_same(a->right, b->right);
        } else {
            return 2;
        }
    }

    return flag == 2 ? 1 : 2;
}
