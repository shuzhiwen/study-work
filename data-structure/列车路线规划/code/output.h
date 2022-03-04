#pragma once

#include "common.h"
#include "init_help.h"
#include "trietree.h"
#include "window.h"

void show_ans(struct trietree *root, struct Vector *vec, char *ear_time, char *begin, char *end,
              char *req);

void ans_print(struct trietree *root, struct Vector *vec, struct trietree **path, int *total, int n,
               char *ear_time, char *begin, char *end, char *req);

void time_fare_tran(struct trietree **path, struct Vector *vec, int *total, char *req, int begin,
                    int end, int n);

void road_print(struct route *road, int n, int fare, int time_ans, int tran);