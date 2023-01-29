#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fds1[2], fds2[2];
    char massage1[1000] = "Child process p1 is sending a message!";
    char massage2[1000] = "Child process p2 is sending a message!";

    if (pipe(fds1) == -1) {
        perror("pipe");
        exit(1);
    }
    if (pipe(fds2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t p1 = fork();

    if (p1 == 0) {  // p1子进程
        printf("I am child process p1, pid: %d\n", getpid());
        if (write(fds1[1], massage1, sizeof(massage1)) == -1) {  // 写
            perror("p1 write");
            exit(1);
        }
        if (read(fds2[0], massage1, sizeof(massage1)) == -1) {  // 读
            perror("p1 read");
            exit(1);
        } else {
            printf("p1: %s\n", massage1);  // 输出
        }
    } else if (p1 > 0) {  // 父进程
        pid_t p2 = fork();

        if (p2 == 0) {  // p2子进程
            printf("I am child process p2, pid: %d\n", getpid());
            if (write(fds2[1], massage2, sizeof(massage2)) == -1) {  // 写
                perror("p2 write");
                exit(1);
            }
            if (read(fds1[0], massage2, sizeof(massage2)) == -1) {  // 读
                perror("p2 read");
                exit(1);
            } else {
                printf("p2: %s\n", massage2);  // 输出
            }
        } else if (p2 > 0) {  // 父进程
        } else {              // 出错
            printf(" error!\n");
        }
    } else {  // 出错
        printf(" error!\n");
    }

    return 0;
}