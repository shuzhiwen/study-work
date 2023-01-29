#include "init_help.h"

// 在字符串中搜索下一个逗号，若找到则返回其下标，否则返回-1
int find_next_comma(char *buffer, int n) {
    char *p = buffer + n;

    while (*p != 0 && *p != ',') {
        p++;
    }

    if (*p == ',') {
        return p - buffer;
    } else {
        return -1;
    }
}

// 初始化站点信息，保存在数组vec中
void station_init(struct Vector *vec) {
    int ser_num = 0;
    char buffer[100];
    char chi_name[20];
    char eng_name[20];

    vector_init(vec, 50);
    FILE *fp = fopen("station.csv", "r");

    fgets(buffer, 100, fp);
    while (fgets(buffer, 100, fp)) {
        int n1, n2;

        n1 = find_next_comma(buffer, 0);
        n2 = find_next_comma(buffer, n1 + 1);
        memcpy(chi_name, buffer + n1 + 1, (n2 - n1 - 1) * sizeof(char));
        chi_name[n2 - n1 - 1] = '\0';

        n1 = find_next_comma(buffer, n2 + 1);
        n2 = find_next_comma(buffer, n1 + 1);
        memcpy(eng_name, buffer + n1 + 1, (n2 - n1 - 1) * sizeof(char));
        eng_name[n2 - n1 - 1] = '\0';

        struct station data;
        data.ser_num = ser_num++;
        strcpy(data.chi_name, chi_name);
        strcpy(data.eng_name, eng_name);
        vector_push_back(vec, data);
    }

    fclose(fp);
}

// 统一时间格式为“xx:xx”
void time_correction(char *t) {
    int n = time_hash_to_int(t);

    t[0] = n / 60 / 10 + '0';
    t[1] = n / 60 % 10 + '0';
    t[2] = ':';
    t[3] = n % 60 / 10 + '0';
    t[4] = n % 60 % 10 + '0';
    t[5] = '\0';
}

// 计算某趟列车的费用
double computing_costs(int time_cost, char type) {
    if (type == 'G') {
        return time_cost * 1.57;
    } else {
        return time_cost * 0.52;
    }
}

// 计算某趟列车的用时
int time_cost(char *dep_time, char *arr_time) {
    int n1 = time_hash_to_int(dep_time);
    int n2 = time_hash_to_int(arr_time);

    if (n1 < n2) {
        return n2 - n1;
    } else {
        return n2 + 24 * 60 - n1;
    }
}

// 初始化列车线路（班次）信息，保存在字典树stat中
int route_init(struct trietree *stat, struct Vector *vec) {
    FILE *fp = fopen("route.csv", "r");

    char tra_num[20];
    char from[20];
    char to[20];
    char dep_time[20];
    char arr_time[20];
    char buffer[100];
    int failed = 0;

    fgets(buffer, 100, fp);
    while (fgets(buffer, 100, fp) != NULL) {
        int n1, n2;

        n1 = find_next_comma(buffer, 0);
        memcpy(tra_num, buffer, n1 * sizeof(char));
        tra_num[n1] = '\0';

        n2 = find_next_comma(buffer, n1 + 1);
        memcpy(from, buffer + n1 + 1, (n2 - n1 - 1) * sizeof(char));
        from[n2 - n1 - 1] = '\0';

        n1 = find_next_comma(buffer, n2 + 1);
        memcpy(to, buffer + n2 + 1, (n1 - n2 - 1) * sizeof(char));
        to[n1 - n2 - 1] = '\0';

        n2 = find_next_comma(buffer, n1 + 1);
        memcpy(dep_time, buffer + n1 + 1, (n2 - n1 - 1) * sizeof(char));
        dep_time[n2 - n1 - 1] = '\0';

        n1 = find_next_comma(buffer, n2 + 1);
        memcpy(arr_time, buffer + n2 + 1, (n1 - n2 - 1) * sizeof(char));
        arr_time[n1 - n2 - 1] = '\0';

        struct route data;
        station_trans_to_engname(vec, from);
        station_trans_to_engname(vec, to);
        strcpy(data.tra_num, tra_num);
        strcpy(data.from, from);
        strcpy(data.to, to);
        strcpy(data.dep_time, dep_time);
        strcpy(data.arr_time, arr_time);
        time_correction(data.dep_time);
        time_correction(data.arr_time);
        data.time_cost = time_cost(data.dep_time, data.arr_time);
        data.fare = computing_costs(data.time_cost, data.tra_num[0]);

        struct trietree *t = trietree_find(stat, from);
        if (t != NULL) {
            list_push_back(&t->l, data);
        } else {
            failed++;
        }
    }

    fclose(fp);
    return failed;
}

// 根据名称查找车站的编号
int station_ser_num(struct Vector *vec, char *s) {
    for (int i = 0; i < vec->size; i++) {
        if (strcmp(s, vector_at(vec, i)->chi_name) == 0 ||
            strcmp(s, vector_at(vec, i)->eng_name) == 0) {
            return vector_at(vec, i)->ser_num;
        }
    }

    return -1;
}

// 将字符串对应的车站英文名称写入字符串
bool station_trans_to_engname(struct Vector *vec, char *s) {
    for (int i = 0; i < vec->size; i++) {
        if (strcmp(s, vector_at(vec, i)->chi_name) == 0 ||
            strcmp(s, vector_at(vec, i)->eng_name) == 0) {
            strcpy(s, vector_at(vec, i)->eng_name);
            return true;
        }
    }

    strcpy(s, "?????");
    return false;
}

// 将字符串表示的时间映射成整型
int time_hash_to_int(char *s) {
    int n1 = 0, n2 = 0;
    char *p = s;

    while (*p != ':' && p - s < strlen(s)) {
        p++;
    }

    if (p - s == 1) {
        n1 += (s[0] - '0') * 60;
    } else if (p - s == 2) {
        n1 += ((s[0] - '0') * 10 + s[1] - '0') * 60;
    }

    while (*(++p) != 0) {
        n2 = n2 * 10 + (*p - '0');
    }

    return n1 + n2;
}

// 判断时间衔接是否合法
bool Is_correct_time_link(int time_limit, char *t) {
    int n = time_hash_to_int(t);

    if (time_limit + waiting_time <= n) {
        return true;
    } else {
        return false;
    }
}

// 判断时间输入的格式是否合法
bool Is_time(char *s) {
    char *p1 = s, *p2 = NULL;

    while (*p1 != ':' && p1 - s < strlen(s)) {
        p1++;
    }

    if (*p1 != ':') {
        return false;
    }
    p2 = p1 + 1;
    p1--;

    while (*p1 <= '9' && *p1 >= '0' && p1 - s >= 0) {
        p1--;
    }
    while (*p2 <= '9' && *p2 >= '0' && p2 - s < strlen(s)) {
        p2++;
    }

    if (s - p1 > 0 && p2 - s >= strlen(s)) {
        return true;
    } else {
        return false;
    }
}