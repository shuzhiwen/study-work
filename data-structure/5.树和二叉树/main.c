#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btree.h"

int main() {
    char *pre = "ABCDEFGHIJKL";
    char *mid = "CBEFDGAJIKLH";
    char *post = "CFEGDBJLKIHA";
    char *level = "ABHCDIEGJKFL";
    char *search = "564387192";
    struct BTree *root1 = NULL, *root2 = NULL, *node = NULL;

    // root = btree_from_pre_mid(pre, mid, strlen(mid));

    root1 = btree_from_post_mid(post, mid, strlen(mid));
    btree_pre_order(root1);  //中序-后序构建二叉树,先序输出
    printf("\n%d leaves\n", btree_leaves(root1));

    root2 = btree_from_level_mid(level, mid, strlen(mid));
    btree_post_order(root2);  //中序-层次构建二叉树,后序输出
    printf("\n%d leaves\n", btree_leaves(root2));

    printf("%d\n\n", btree_is_same(root1, root2));  //判断两棵树是否相同

    root1 = btree_build_search_tree(search);
    btree_level_order(root1);       //构建二叉搜索树,层次输出
    node = btree_find(root1, '9');  //二叉搜索树查找
    printf("\n%c\n", node->data);

    //同构的两棵树
    root1 = btree_from_pre_mid("ABDEC", "DBEAC", 5);
    root2 = btree_from_pre_mid("ACBDE", "CADBE", 5);
    printf("\n%d\n", btree_is_isomorphic(root1, root2));
    //不同构的两棵树
    root1 = btree_from_pre_mid("ABDEC", "DBEAC", 5);
    root2 = btree_from_pre_mid("ABCDE", "BADCE", 5);
    printf("\n%d\n", btree_is_isomorphic(root1, root2));

    btree_destroy(root1);
    btree_destroy(root2);
}
