#pragma once

#include "list.h"
#include "vector.h"

void filetree_init(struct FileTree *node, bool isDirectory, char *name, struct File *file);

void filetree_free(struct FileTree *node);

void ls(struct FileTree *node);

void cd(struct FileTree **node, struct FileTree *root, char *route);

void makedir(struct FileTree *node, char *name);

void makefile(struct Vector *vec, struct FileTree *node, char *name);

void delnode(struct Vector *vec, bool isDirectory, struct FileTree *node, char *name);

void show(struct FileTree *node);