#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PNUM 5    // 进程的数量
#define TIMER 10  // 定时器,最长CPU区间时间
#define SLICE 2   // 轮转算法的时间片

typedef struct node {
    int pid;            // 进程号
    int priority;       // 进程优先级,1~3,数字越小优先级越高
    int arrival;        // 到达时间
    int burst;          // CPU区间时间
    int rest;           // 剩余时间
    char state;         // 进程状态,'N'新建,'R'运行,'W'等待CPU(就绪),'T'终止
    struct node *next;  // 指向队列中下一个进程的PCB
} PCB;

int timenow = 0;                // 当前时刻,模拟时钟滴答
int gantt[TIMER * PNUM] = {0};  // 用一个数组记录调度过程,每个时刻调度的进程号

PCB *job;           // 所有作业的序列,带头节点(为简化编程)
PCB *ready = NULL;  // 进程就绪队列,不带头节点
PCB *tail = NULL;   // 记录就绪队列的尾节点
PCB *run = NULL;  // 正在运行中的进程,不带头结点，任意时刻最多仅一个进程。
PCB *finish = NULL;  // 已经结束的程序,不带头结点，所有进程将按结束先后顺序移入该链表

void pushJob(PCB pcb[PNUM]) {  // 链接进程并放入job链表
    job = (PCB *)malloc(sizeof(PCB));
    job->next = pcb;
    for (int i = 0; i < PNUM - 1; i++) {
        pcb[i].next = pcb + i + 1;
    }
}

void pushReady(PCB *job) {  // 遍历job，将到达的进程放入ready
    PCB *tmp = job->next;
    PCB *prev = job;

    while (tmp != NULL) {
        if (tmp->arrival == timenow) {  // 进程到达
            prev->next = tmp->next;
            if (ready == NULL) {
                ready = tail = tmp;
            } else {
                tail->next = tmp;
                tail = tmp;
            }
            tail->next = NULL;
            tail->state = 'W';
        } else {
            prev = prev->next;
        }
        tmp = prev->next;
    }
}

void printInit(PCB pcb[PNUM]) {  // 打印初始化信息
    for (int i = 0; i < PNUM; i++) {
        printf("pid: %d   ", pcb[i].pid);
        printf("arrival: %d   ", pcb[i].arrival);
        printf("burst: %d   ", pcb[i].burst);
        printf("priority: %d\n", pcb[i].priority);
        printf("-----------------------------------------------\n");
    }
}

void printAnswer() {  // 打印结果
    printf("timenow: %d\n", timenow);
    printf("reverse order of results: \n");
    for (PCB *tmp = finish; tmp != NULL; tmp = tmp->next) {
        printf("--PID: %d\n", tmp->pid);
    }
    for (int i = 0; i < TIMER * PNUM; i++) {
        if (gantt[i] == 0) {
            continue;
        } else {
            printf("process' pid for time %d: %d\n", i, gantt[i]);
        }
    }
}

void FCFS(PCB pcb[PNUM]) {
    pushJob(pcb);
    while (job->next != NULL || ready != NULL || run != NULL) {
        pushReady(job);
        if (run == NULL && ready != NULL) {  // run中无进程,将ready中的第一个进程放入run中
            run = ready;
            run->state = 'R';
            ready = ready->next;
            if (ready == NULL) {
                tail = NULL;
            }
        }
        if (run != NULL) {  // run中的进程没有执行完毕,继续执行
            run->rest--;
            gantt[timenow] = run->pid;
            if (run->rest == 0) {  // 执行完毕
                run->state = 'T';
                run->next = finish;
                finish = run;
                run = NULL;
            }
        }
        timenow++;
    }
}

PCB *findShortest_prev() {  // 找到ready队列中耗时最短进程的前一个进程
    PCB *tmp = ready;
    PCB *Shortest_prev = ready;

    while (tmp != NULL && tmp->next != NULL) {
        if (tmp->next->rest < Shortest_prev->next->rest &&
            tmp->next->rest < Shortest_prev->rest) {  // 特殊情况
            Shortest_prev = tmp;
        }
        tmp = tmp->next;
    }
    return Shortest_prev;  // 返回耗时最短进程的前一个进程,或者返回ready
}

void SJF(PCB pcb[PNUM]) {
    pushJob(pcb);
    while (job->next != NULL || ready != NULL || run != NULL) {
        pushReady(job);
        if (run == NULL && ready != NULL) {  // run中无进程,ready队列中耗时最短的进程放入run中
            PCB *Shortest_prev = findShortest_prev();

            if (Shortest_prev != NULL) {
                if (Shortest_prev->next == NULL ||
                    Shortest_prev->next->rest > Shortest_prev->rest) {
                    run = ready;
                    ready = ready->next;
                    if (ready == NULL) {
                        tail = NULL;
                    }
                } else {  // 返回的不是ready
                    run = Shortest_prev->next;
                    if (run == tail) {
                        tail = Shortest_prev;
                    }
                    Shortest_prev->next = Shortest_prev->next->next;
                }
                run->state = 'R';
            }
        }
        if (run != NULL) {  // run中的进程没有执行完毕,继续执行
            run->rest--;
            gantt[timenow] = run->pid;
            if (run->rest == 0) {  // 执行完毕
                run->state = 'T';
                run->next = finish;
                finish = run;
                run = NULL;
            }
        }
        timenow++;
    }
}

void SRTF(PCB pcb[PNUM]) {
    pushJob(pcb);
    while (job->next != NULL || ready != NULL || run != NULL) {
        pushReady(job);
        if (run == NULL && ready != NULL) {  // run中无进程,ready队列中耗时最短的进程放入run中
            PCB *Shortest_prev = findShortest_prev();

            if (Shortest_prev != NULL) {
                if (Shortest_prev->next == NULL ||
                    Shortest_prev->next->rest > Shortest_prev->rest) {
                    run = ready;
                    ready = ready->next;
                    if (ready == NULL) {
                        tail = NULL;
                    }
                } else {  // 返回的不是ready
                    run = Shortest_prev->next;
                    if (run == tail) {
                        tail = Shortest_prev;
                    }
                    Shortest_prev->next = Shortest_prev->next->next;
                }
                run->state = 'R';
            }
        }
        if (run != NULL) {  // run中的进程没有执行完毕,继续执行
            run->rest--;
            gantt[timenow] = run->pid;
            if (run->rest == 0) {  // 执行完毕
                run->state = 'T';
                run->next = finish;
                finish = run;
                run = NULL;
            } else {  // SRTF在SJF的基础上改造,每次都会检查ready队列中的最短剩余时间
                if (ready == NULL) {
                    ready = tail = run;
                } else {
                    tail->next = run;
                    tail = run;
                }
                tail->next = NULL;
                tail->state = 'W';
                run = NULL;
            }
        }
        timenow++;
    }
}

void RR(PCB pcb[PNUM]) {
    pushJob(pcb);
    while (job->next != NULL || ready != NULL || run != NULL) {
        pushReady(job);
        if (run == NULL && ready != NULL) {  // run中无进程,将ready中的第一个进程放入run中
            run = ready;
            run->state = 'R';
            ready = ready->next;
            if (ready == NULL) {
                tail = NULL;
            }
        }
        if (run != NULL) {  // 处理一个时间片
            for (int i = 0; i < SLICE; i++) {
                run->rest--;
                gantt[timenow++] = run->pid;
                if (run->rest == 0) {  // 执行完毕
                    run->state = 'T';
                    run->next = finish;
                    finish = run;
                    run = NULL;
                    break;
                }
                pushReady(job);
            }
            if (run != NULL) {  // 还未执行完,放入ready尾部
                if (ready == NULL) {
                    ready = tail = run;
                } else {
                    tail->next = run;
                    tail = run;
                }
                tail->next = NULL;
                tail->state = 'W';
                run = NULL;
            }
        } else {
            timenow++;
        }
    }
}

PCB *findMaxPriority_prev() {  // 找到ready队列中最高优先级进程的前一个进程
    PCB *tmp = ready;
    PCB *Shortest_prev = ready;

    while (tmp != NULL && tmp->next != NULL) {
        if (tmp->next->priority < Shortest_prev->next->priority &&
            tmp->next->priority < Shortest_prev->priority) {  // 特殊情况
            Shortest_prev = tmp;
        }
        tmp = tmp->next;
    }
    return Shortest_prev;  // 返回最高优先级进程的前一个进程,或者返回ready
}

void Priority(PCB pcb[PNUM]) {
    pushJob(pcb);
    while (job->next != NULL || ready != NULL || run != NULL) {
        pushReady(job);
        if (run == NULL && ready != NULL) {  // run中无进程,ready队列中耗时最短的进程放入run中
            PCB *Shortest_prev = findMaxPriority_prev();  // 在SJF的基础上改变了寻找函数

            if (Shortest_prev != NULL) {
                if (Shortest_prev->next == NULL ||
                    Shortest_prev->next->priority > Shortest_prev->priority) {
                    run = ready;
                    ready = ready->next;
                    if (ready == NULL) {
                        tail = NULL;
                    }
                } else {  // 返回的不是ready
                    run = Shortest_prev->next;
                    if (run == tail) {
                        tail = Shortest_prev;
                    }
                    Shortest_prev->next = Shortest_prev->next->next;
                }
                run->state = 'R';
            }
        }
        if (run != NULL) {  // run中的进程没有执行完毕,继续执行
            run->rest--;
            gantt[timenow] = run->pid;
            if (run->rest == 0) {  // 执行完毕
                run->state = 'T';
                run->next = finish;
                finish = run;
                run = NULL;
            } else {  // Priority在SJF的基础上改造,每次都会检查ready队列中的最高优先级进程
                if (ready == NULL) {
                    ready = tail = run;
                } else {
                    tail->next = run;
                    tail = run;
                }
                tail->next = NULL;
                tail->state = 'W';
                run = NULL;
            }
        }
        timenow++;
    }
}

int main() {
    PCB *pcb = (PCB *)malloc(sizeof(PCB) * PNUM);

    srand((unsigned)time(NULL));
    for (int i = 0; i < PNUM; i++) {
        pcb[i].pid = rand() % 8000 + 1000;
        pcb[i].priority = rand() % 3 + 1;
        pcb[i].arrival = rand() % 5;
        pcb[i].burst = rand() % TIMER + 1;
        pcb[i].rest = pcb[i].burst;
        pcb[i].state = 'N';
        pcb[i].next = NULL;
    }

    printInit(pcb);
    FCFS(pcb);
    // SJF(pcb);
    // SRTF(pcb);
    // RR(pcb);
    // Priority(pcb);
    printAnswer();
}
