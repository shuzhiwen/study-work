#include "file.h"

void filetree_init(struct FileTree *node, bool isDirectory, char *name, struct File *file) {
    struct List *list = (struct List *)malloc(sizeof(struct List));

    node->isDirectory = isDirectory;
    node->file = file;
    node->children = list;
    strcpy(node->name, name);

    list_init(node->children);
}

void filetree_free(struct FileTree *node) {
    struct ListNode *tmp = node->children->head;

    while (tmp != NULL) {
        filetree_free(&(tmp->data));
        tmp = tmp->next;
    }

    list_destroy(node->children);
}

//枚举目录或文件
void ls(struct FileTree *node) {
    struct ListNode *tmp = node->children->head;

    while (tmp != NULL) {
        printf("\t[%s]\t%s\n", tmp->data.isDirectory == true ? "dir" : "file", tmp->data.name);
        tmp = tmp->next;
    }
}

struct ListNode *findExist(struct FileTree *node, char *name, bool isDirectory) {
    struct ListNode *tmp = node->children->head;

    while (tmp != NULL) {
        if (strcmp(tmp->data.name, name) == 0 && tmp->data.isDirectory == isDirectory) return tmp;

        tmp = tmp->next;
    }

    return NULL;
}

//变更路径，不支持多层访问
void cd(struct FileTree **node, struct FileTree *root, char *route) {
    struct ListNode *tmp = findExist(*node, route, true);

    if (strcmp(route, "root") == 0) {
        *node = root;
        return;
    }

    if (tmp != NULL)
        *node = &(tmp->data);
    else
        printf("目录不存在\n");
}

//创建目录
void makedir(struct FileTree *node, char *name) {
    struct FileTree fileTree;

    if (findExist(node, name, true) != NULL) {  //检测同名目录是否存在
        printf("目录已存在\n");
        return;
    }

    filetree_init(&fileTree, true, name, NULL);  //初始化目录树结点
    list_push_back(node->children, fileTree);    //挂载到目录树
}

//创建文件
void makefile(struct Vector *vec, struct FileTree *node, char *name) {
    struct File file;
    struct FileTree fileTree;
    int index;

    if (findExist(node, name, false) != NULL) {  //检测同名文件是否存在
        printf("文件已存在\n");
        return;
    }

    strcpy(file.name, name);
    index = vector_find_first(vec, file);

    if (index == -1) {  // Vector中没有此文件
        file.count = 1;
        vector_push_back(vec, file);  //添加文件到Vector
        index = vec->size - 1;
    } else {
        vector_at(vec, index)->count++;
    }

    filetree_init(&fileTree, false, name, vector_at(vec, index));  //初始化目录树结点
    list_push_back(node->children, fileTree);                      //挂载到目录树
}

//递归删除目录树
void delete (struct Vector *vec, struct FileTree *node) {
    struct ListNode *tmp = node->children->head;

    while (tmp != NULL) {
        if (tmp->data.isDirectory == false) {  //目录树结点是文件
            tmp->data.file->count--;
            if (tmp->data.file->count == 0) vector_delete_value(vec, *(tmp->data.file));
        } else {  //目录树结点是目录
            delete (vec, &(tmp->data));
        }

        tmp = tmp->next;
        list_pop_front(node->children);  //从目录树中卸载
    }
}

//删除目录或文件
void delnode(struct Vector *vec, bool isDirectory, struct FileTree *node, char *name) {
    struct ListNode *tmp = findExist(node, name, isDirectory);
    struct ListNode *tmp_prev = NULL;

    if (tmp == NULL) {  //检测同名目录/文件是否存在
        if (isDirectory)
            printf("目录不存在\n");
        else
            printf("文件不存在\n");

        return;
    }

    if (isDirectory) {  //目录
        delete (vec, &(tmp->data));
    } else {  //文件
        tmp->data.file->count--;
        if (tmp->data.file->count == 0) vector_delete_value(vec, *(tmp->data.file));
    }

    //从目录树中卸载
    tmp_prev = list_prev(node->children, tmp);
    if (tmp_prev == NULL)
        list_pop_front(node->children);
    else
        list_remove_after(node->children, tmp_prev);
}

void dot(struct FileTree *node, FILE *fp) {
    struct ListNode *tmp = node->children->head;

    while (tmp != NULL) {
        dot(&(tmp->data), fp);
        fprintf(fp, "\t%s -- %s\n", node->name, tmp->data.name);
        tmp = tmp->next;
    }
}

//将树导出为dot文件
void show(struct FileTree *node) {
    FILE *fp = fopen("data.dot", "w");

    if (fp == NULL) printf("文件操作异常\n");

    fprintf(fp, "graph tree {\n");
    dot(node, fp);
    fprintf(fp, "}");

    fclose(fp);
}