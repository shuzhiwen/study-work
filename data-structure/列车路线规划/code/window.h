#pragma once

#include "common.h"
#include "init_help.h"
#include "output.h"
#include "trietree.h"

void transformation_scene(struct trietree *root, struct Vector *v, int sign);

void main_window(struct trietree *root, struct Vector *v, int sign);

int first(struct trietree *root, struct Vector *v, int sign);

int second(struct trietree *root, struct Vector *v, int sign);

int third(struct trietree *root, struct Vector *v, int sign);

int fourth(struct trietree *root, struct Vector *v, int sign);