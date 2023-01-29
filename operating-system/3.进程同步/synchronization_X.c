#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define operationNumber 55  // 消费者或者生产者操作次数
#define bufferSize 10       // 缓冲数目

sem_t empty_sem;        // 同步信号量,当满了时阻止生产者放产品
sem_t full_sem;         // 同步信号量,当没产品时阻止消费者消费
pthread_mutex_t mutex;  // 互斥信号量,一次只有一个线程访问缓冲

char buff[bufferSize] = "----------";  // 缓冲初始化为-， 开始时没有产品
int operation_n = 0;                   // 生产者和消费者总操作数

void print() {
    for (int i = 0; i < bufferSize; i++) {  // 打印buff
        putchar(buff[i]);
    }
    putchar('\n');
}

/* 生产者方法 */
void* produce() {
    while (operation_n < operationNumber) {
        sem_wait(&empty_sem);
        pthread_mutex_lock(&mutex);

        printf("%2d producer write X: ", operation_n);
        for (int i = 0; i < bufferSize; i++) {  // 写入数据
            if (buff[i] == '-') {
                buff[i] = 'X';
                break;
            }
        }
        print();
        operation_n++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full_sem);
    }
}

/* 消费者方法 */
void* consume() {
    while (operation_n < operationNumber) {
        sem_wait(&full_sem);
        pthread_mutex_lock(&mutex);

        printf("%2d customer  read X: ", operation_n);
        for (int i = 0; i < bufferSize; i++) {  // 取出数据
            if (buff[i] == 'X') {
                buff[i] = '-';
                break;
            }
        }
        print();
        operation_n++;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty_sem);
    }
}

int main() {
    pthread_t producer;
    pthread_t customer;
    int ret;

    // 初始化同步信号量
    int ini1 = sem_init(&empty_sem, 0, bufferSize);
    int ini2 = sem_init(&full_sem, 0, 0);
    if (ini1 && ini2 != 0) {
        printf("sem init failed \n");
        exit(1);
    }
    // 初始化互斥信号量
    int ini3 = pthread_mutex_init(&mutex, NULL);
    if (ini3 != 0) {
        printf("mutex init failed \n");
        exit(1);
    }
    // 创建生产者线程
    ret = pthread_create(&producer, NULL, produce, NULL);
    if (ret != 0) {
        printf("produce creation failed \n");
        exit(1);
    }
    // 创建消费者线程
    ret = pthread_create(&customer, NULL, consume, NULL);
    if (ret != 0) {
        printf("consume creation failed \n");
        exit(1);
    }
    // 销毁线程
    pthread_join(producer, NULL);
    pthread_join(customer, NULL);

    exit(0);
}