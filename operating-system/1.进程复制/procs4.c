#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("I am main process\n");

    pid_t p1 = fork();

    if (p1 == 0) {  // p1子进程
        printf("I am child process p1, pid: %d\n", getpid());

        pid_t p3 = fork();

        if (p3 == 0) {  // p3子进程
            printf("I am child process p3, pid: %d\n", getpid());
        } else if (p3 > 0) {  // p1父进程
            printf("p1: I'm p3's father\n");
        } else {  // p1出错
            printf("p1 error!\n");
        }
    } else if (p1 > 0) {  // procs4父进程
        printf("procs4: I'm p1's father\n");

        pid_t p2 = fork();

        if (p2 == 0) {  // p2子进程
            printf("I am child process p2, pid: %d\n", getpid());
        } else if (p2 > 0) {  // procs4父进程
            printf("procs4: I'm p2's father\n");
        } else {  // procs4出错
            printf("procs4 error!\n");
        }
    } else {  // procs4出错
        printf("procs4 error!\n");
    }

    execl("/bin/ls", "ls", "-l", NULL);

    return 0;
}
