#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define n 5  // 进程数量
#define m 4  // 资源类型数量

int Available[m] = {1, 5, 2, 0};  // 可用资源，m个资源类型
int Max[n][m] = {                 // n个进程提交的最大资源需求
    {0, 0, 1, 2},
    {1, 7, 5, 0},
    {2, 3, 5, 6},
    {0, 6, 5, 2},
    {0, 6, 5, 6}};
int Allocation[n][m] = {  // n个进程已获得的资源
    {0, 0, 1, 2},
    {1, 0, 0, 0},
    {1, 3, 5, 4},
    {0, 6, 3, 2},
    {0, 0, 1, 4}};
int Need[n][m];  // n个进程还需要的资源

void countNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

bool isSafe() {
    int Work[m];
    bool Finish[n] = {false};

    for (int i = 0; i < m; i++) {
        Work[i] = Available[i];
    }

    for (int i = 0; i < n; i++) {
        bool isNeedExceedWork = false;

        if (Finish[i] == false) {
            for (int j = 0; j < m; j++) {
                if (Need[i][j] > Work[j]) {  // 不满足条件
                    isNeedExceedWork = true;
                    break;
                }
            }
            if (!isNeedExceedWork) {  // 满足条件时
                for (int j = 0; j < m; j++) {
                    Work[j] += Allocation[i][j];
                }
                Finish[i] = true;
                i = -1;  // 寻找一下个满足条件的进程
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (Finish[i] == false) {  // 不安全
            return false;
        }
    }

    return true;  // 安全
}

void banker(int process, int* request) {
    for (int i = 0; i < m; i++) {
        if (request[i] > Need[process][i]) {
            printf("资源分配失败：申请的资源大于需要的资源\n");
            printf("出错进程：P%d\n", process);
            return;
        }
    }

    for (int i = 0; i < m; i++) {
        if (request[i] > Available[i]) {
            printf("资源分配失败：可用资源不足\n");
            printf("出错进程：P%d\n", process);
            return;
        }
    }

    for (int i = 0; i < m; i++) {  // 虚拟分配，用以检测系统是否处于安全状态
        Available[i] -= request[i];
        Allocation[process][i] += request[i];
        Need[process][i] -= request[i];
    }

    if (isSafe()) {
        printf("资源分配成功\n");
        printf("成功进程：P%d\n", process);
    } else {
        printf("资源分配失败：系统处于不安全状态\n");
        printf("出错进程：P%d\n", process);
        for (int i = 0; i < m; i++) {  // 恢复原状态
            Available[i] += request[i];
            Allocation[process][i] -= request[i];
            Need[process][i] += request[i];
        }
    }
}

int main() {
    int request1[3] = {0, 4, 2, 0};

    countNeed();
    printf("%s\n", isSafe() ? "safe" : "not safe");
    banker(1, request1);
}