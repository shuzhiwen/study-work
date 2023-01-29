#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define waiting_time 20

struct station {
    int ser_num;        // 编号
    char chi_name[20];  // 中文名
    char eng_name[20];  // 英文名
};

struct route {
    double fare;        // 费用
    char tra_num[20];   // 列车号
    char from[20];      // 出发地
    char to[20];        // 目的地
    char dep_time[20];  // 发车时刻
    char arr_time[20];  // 到达时刻
    int time_cost;
};

enum Status {
    STATUS_OK = 0,

    STATUS_ERR_ALLOC = 1,
    STATUS_ERR_INVALID_CAPACITY = 2,
    STATUS_ERR_INVALID_RANGE = 3,
    STATUS_ERR_MAX_CAPACITY = 4,
    STATUS_ERR_KEY_NOT_FOUND = 6,
    STATUS_ERR_VALUE_NOT_FOUND = 7,
    STATUS_ERR_OUT_OF_RANGE = 8,

    STATUS_ITER_END = 9,
};

#define SWAP(x, y, T) \
    do {              \
        T SWAP = x;   \
        x = y;        \
        y = SWAP;     \
    } while (0)
