#pragma once

#include "common.h"
#include "list.h"
#include "trietree.h"
#include "vector.h"

void time_correction(char *t);

void station_init(struct Vector *vec);

bool Is_time(char *s);

bool Is_correct_time_link(int time_limit, char *t);

bool station_trans_to_engname(struct Vector *vec, char *s);

int time_hash_to_int(char *t);

int time_cost(char *dep_time, char *arr_time);

int station_ser_num(struct Vector *vec, char *s);

int route_init(struct trietree *stat, struct Vector *vec);