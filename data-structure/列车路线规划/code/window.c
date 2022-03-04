#include "window.h"

char ear_time[10], req[20], begin[20], end[20];

//输入用户需求
int fourth(struct trietree *root, struct Vector *v, int sign) {
    main_window(root, v, sign);

    if (sign == 7) {
        printf("\t     Let's continue, What's your requirement ?\n\n");
    } else if (sign == 8) {
        printf("\tYour input is wrong ! Please reinput the requirement !\n\n");
    }

    printf("     A. Shortest time    B. Minimum cost    C. Minimum transfer\n\n");
    printf("\t     INPUT : ");
    scanf("%s", req);

    if (strlen(req) == 1 && req[0] <= '4' && req[0] >= '1') {
        sign = (req[0] - '0') * 2 - 1;
        strcpy(req, "?????");
    } else if (req[0] == 'a' || req[0] == 'A' || req[0] == 'b' || req[0] == 'B' || req[0] == 'c' ||
               req[0] == 'C') {
        if (req[0] == 'a' || req[0] == 'A') {
            strcpy(req, "Shortest time");
        } else if (req[0] == 'b' || req[0] == 'B') {
            strcpy(req, "Minimum cost");
        } else if (req[0] == 'c' || req[0] == 'C') {
            strcpy(req, "Minimum transfer");
        }
        sign = 9;
    } else {
        sign = 8;
    }

    transformation_scene(root, v, sign);
}

//输入目的地
int third(struct trietree *root, struct Vector *v, int sign) {
    main_window(root, v, sign);

    if (sign == 5) {
        printf("\t    Let's continue, Where do you want to go ?\n\n");
    } else if (sign == 6) {
        printf("\tYour input is wrong ! Please reinput the destination !\n\n");
    }

    printf("\t    INPUT : ");
    scanf("%s", end);

    if (strlen(end) == 1 && end[0] <= '4' && end[0] >= '1') {
        sign = (end[0] - '0') * 2 - 1;
        strcpy(end, "?????");
    } else if (station_trans_to_engname(v, end) && trietree_find(root, end) != NULL) {
        sign = 7;
    } else {
        sign = 6;
    }

    transformation_scene(root, v, sign);
}

//输入出发地
int second(struct trietree *root, struct Vector *v, int sign) {
    main_window(root, v, sign);

    if (sign == 3) {
        printf("\t    Let's continue, Where do you want to set out ?\n\n");
    } else if (sign == 4) {
        printf("\tYour input is wrong ! Please reinput the position !\n\n");
    }

    printf("\t    INPUT : ");
    scanf("%s", begin);

    if (strlen(begin) == 1 && begin[0] <= '4' && begin[0] >= '1') {
        sign = (begin[0] - '0') * 2 - 1;
        strcpy(begin, "?????");
    } else if (station_trans_to_engname(v, begin) && trietree_find(root, begin) != NULL) {
        sign = 5;
    } else {
        sign = 4;
    }

    transformation_scene(root, v, sign);
}

//输入时间
int first(struct trietree *root, struct Vector *v, int sign) {
    main_window(root, v, sign);

    if (sign == 1) {
        printf("\t    Let's start, When are you going to leave ?\n\n");
    } else if (sign == 2) {
        printf("\tYour input is wrong ! Please reinput the time !\n\n");
    }

    printf("\t    INPUT : ");
    scanf("%s", ear_time);

    if (strlen(ear_time) == 1 && ear_time[0] <= '4' && ear_time[0] >= '1') {
        sign = (ear_time[0] - '0') * 2 - 1;
        strcpy(ear_time, "?????");
    } else if (Is_time(ear_time) == true) {
        sign = 3;
    } else {
        sign = 2;
    }

    transformation_scene(root, v, sign);
}

//转换“场景”
void transformation_scene(struct trietree *root, struct Vector *v, int sign) {
    if (abs(sign) < 1) {
        main_window(root, v, sign);
    } else if (abs(sign) < 3) {
        first(root, v, sign);
    } else if (abs(sign) < 5) {
        second(root, v, sign);
    } else if (abs(sign) < 7) {
        third(root, v, sign);
    } else if (abs(sign) < 9) {
        fourth(root, v, sign);
    } else {
        show_ans(root, v, ear_time, begin, end, req);
    }
}

//主界面的显示
void main_window(struct trietree *root, struct Vector *v, int sign) {
    system("clear");

    puts(" ————————————————————————————————————————————————————————————————");
    puts("|            Welcome into the traffic inquiry system !           |");
    puts("|                                                                |");
    puts("|        Please enter a number to continue the operation !       |");
    puts(" ————————————————————————————————————————————————————————————————\n");

    printf("   1. %s the departure time.", sign > 1 ? "Reinput" : "Input");
    printf("\t 2. %s the current position.\n\n", sign > 3 ? "Reinput" : "Input");
    printf("   3. %s the destination.", sign > 5 ? "Reinput" : "Input");
    printf("\t 4. %s the requirements.\n\n", sign > 7 ? "Reinput" : "Input");

    if (sign == 0) {
        strcpy(ear_time, "?????");
        strcpy(begin, "?????");
        strcpy(end, "?????");
        strcpy(req, "?????");
    }

    printf(" ————————————————————————————————————————————————————————————————\n");
    printf("   Earliest time: %s           \tDeparture: %s\n", ear_time, begin);
    printf(" ————————————————————————————————————————————————————————————————\n");
    printf("   Destination: %s           \tRequirement: %s\n", end, req);
    printf(" ————————————————————————————————————————————————————————————————\n\n");

    if (sign == 0) {
        transformation_scene(root, v, 1);
    }
}