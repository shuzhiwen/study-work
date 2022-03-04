#include "output.h"

#define INF 29999

//更新图的信息
void relax(struct trietree **path, struct Vector *vec, struct trietree *cur, int time_limit,
           char *req, int *total) {
    int interim, target;
    double tmp = INF;
    struct ListNode *p;

    for (p = cur->l.head; p != NULL; p = p->next) {
        if (Is_correct_time_link(time_limit, p->data.dep_time) == true) {
            interim = station_ser_num(vec, cur->data);
            target = station_ser_num(vec, p->data.to);

            if (strcmp(req, "Shortest time") == 0) {
                tmp = total[interim] + p->data.time_cost;
            } else if (strcmp(req, "Minimum cost") == 0) {
                tmp = p->data.fare + total[interim];
            } else if (strcmp(req, "Minimum transfer") == 0) {
                tmp = total[interim] + 1;
            }

            if (tmp < total[target]) {
                total[target] = (int)tmp;
                path[target] = cur;
            }
        }
    }
}

//寻找下一个站点
int find_next_station(struct Vector *vec, int *total, bool *visited) {
    int target = 0, tmp = INF;

    for (int i = 0; i < vec->size; i++) {
        if (visited[i] == false && total[i] < tmp) {
            tmp = total[i];
            target = i;
        }
    }

    return target;
}

//更新时间限制
void update_time_limit(struct Vector *vec, int *time_limit, struct trietree **path, int next_num) {
    struct ListNode *p = NULL;

    for (p = path[next_num]->l.head; p != NULL; p = p->next) {
        if (strcmp(vector_at(vec, next_num)->eng_name, p->data.to) == 0) {
            *time_limit = time_hash_to_int(p->data.arr_time);
            break;
        }
    }
}

void show_ans(struct trietree *root, struct Vector *vec, char *ear_time, char *begin, char *end,
              char *req) {
    int cur_num, stats = vec->size;
    int total[stats], time_limit = time_hash_to_int(ear_time);
    bool visited[stats];
    struct trietree *path[stats], *cur = NULL;

    for (int i = 0; i < stats; i++) {
        path[i] = NULL;
    }
    for (int i = 0; i < stats; i++) {
        total[i] = INF;
    }
    for (int i = 0; i < stats; i++) {
        visited[i] = false;
    }

    cur_num = station_ser_num(vec, begin);  // cur_num保存begin对应站点的编号
    total[cur_num] = 0;
    while (visited[cur_num] != true) {
        visited[cur_num] = true;  //标记已访问

        // cur保存cur_num对应站点在字典树中的地址
        cur = trietree_find(root, vector_at(vec, cur_num)->eng_name);
        relax(path, vec, cur, time_limit, req, total);
        cur_num = find_next_station(vec, total, visited);
        update_time_limit(vec, &time_limit, path, cur_num);
    }

    ans_print(root, vec, path, total, vec->size, ear_time, begin, end, req);
}

//输出窗口的初始化
void ans_print(struct trietree *root, struct Vector *vec, struct trietree **path, int *total, int n,
               char *ear_time, char *begin, char *end, char *req) {
    system("clear");

    printf(" ————————————————————————————————————————————————————————————————\n");
    printf("   Earliest time: %s           \tDeparture: %s\n", ear_time, begin);
    printf(" ————————————————————————————————————————————————————————————————\n");
    printf("   Destination: %s           \tRequirement: %s\n", end, req);
    printf(" ————————————————————————————————————————————————————————————————\n\n");

    int n1 = station_ser_num(vec, begin);
    int n2 = station_ser_num(vec, end);
    char input[20];

    if (total[n2] != INF) {
        printf("    Luckily ! We find a route from %s to %s !\n\n", begin, end);
        time_fare_tran(path, vec, total, req, n1, n2, n);
    } else {
        printf("\t     Unfortunately ! There is no train today !\n\n");
    }

    printf(" ————————————————————————————————————————————————————————————————\n");
    printf("\t\t    Please enter E(e) to exit\n");
    printf("\t  or any other words return to the main interface !\n");
    printf(" ————————————————————————————————————————————————————————————————\n\n");
    printf("\t\t    Input : ");
    scanf("%s", input);
    if (input[0] != 'e' && input[0] != 'E') {
        main_window(root, vec, 0);
    }
}

//计算总时间，总花费，总中转次数
void time_fare_tran(struct trietree **path, struct Vector *vec, int *total, char *req, int begin,
                    int end, int n) {
    int fare_ans = 0, time_ans = 0, tran_ans = 0, i = end, road_i = 0;
    struct route *road = malloc(sizeof(struct route *) * n);
    char waitingtime[20];

    while (total[i] != INF && i != begin && path[i] != NULL) {
        struct trietree *from = path[i];
        struct ListNode *p = from->l.head;

        while (p != NULL) {
            if (strcmp(p->data.to, vector_at(vec, i)->eng_name) == 0) {
                break;
            } else {
                p = p->next;
            }
        }

        tran_ans++;
        road[road_i++] = p->data;
        fare_ans += p->data.fare;
        time_ans += p->data.time_cost;
        if (i != end) {
            time_ans += time_cost(p->data.arr_time, waitingtime);
        }

        i = station_ser_num(vec, from->data);
        strcpy(waitingtime, p->data.dep_time);
    }

    road_print(road, road_i, fare_ans, time_ans, tran_ans);
    free(road);
}

//输出乘车步骤
void road_print(struct route *road, int n, int fare, int time_ans, int tran) {
    for (int i = n - 1; i >= 0; i--) {
        printf("\tStep %d: Train: %s   %s => %s\n", n - i, road[i].tra_num, road[i].from,
               road[i].to);
        printf("\t        Time:  %s --- %s\n", road[i].dep_time, road[i].arr_time);
    }

    printf("\n\tTotal cost: %d RMB\n", fare);
    printf("\tTotal time: %d H %d M\n", time_ans / 60, time_ans % 60);
    printf("\tTotal transfer: %d\n\n", tran);
}