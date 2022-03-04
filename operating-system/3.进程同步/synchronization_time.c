#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define operationNumber 10  //消费者或者生产者操作次数
#define bufferSize 5        //缓冲数目

sem_t empty_sem;        //同步信号量,当满了时阻止生产者放产品
sem_t full_sem;         //同步信号量,当没产品时阻止消费者消费
pthread_mutex_t mutex;  //互斥信号量,一次只有一个线程访问缓冲

long buff[operationNumber] = {0};  //缓冲初始化为0， 开始时没有产品
int produce_n = 0;                 //生产者第n次操作
int consume_n = 0;                 //消费者第n次操作
int put_order = 0;                 //生产者操作的buff下标
int get_order = 0;                 //消费者操作的buff下标
struct timeval tv;

/* 生产者方法 */
void* produce() {
    for (int i = 0; i < operationNumber; i++) {
        int n = ++produce_n;

        sem_wait(&empty_sem);
        pthread_mutex_lock(&mutex);

        printf("%2d producer puts time in the buffer: ", n);
        gettimeofday(&tv, NULL);
        printf("%ld\n", tv.tv_usec);
        buff[put_order++] = tv.tv_usec;

        pthread_mutex_unlock(&mutex);
        sem_post(&full_sem);
    }
}

/* 消费者方法 */
void* consume() {
    for (int i = 0; i < operationNumber; i++) {
        int n = ++consume_n;

        sem_wait(&full_sem);
        pthread_mutex_lock(&mutex);

        printf("%2d customer gets time in the buffer: ", n);
        printf("%ld\n", buff[get_order++]);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty_sem);
    }
}

int main() {
    pthread_t producer;
    pthread_t customer;
    int ret;

    //初始化同步信号量
    int ini1 = sem_init(&empty_sem, 0, bufferSize);
    int ini2 = sem_init(&full_sem, 0, 0);
    if (ini1 && ini2 != 0) {
        printf("sem init failed \n");
        exit(1);
    }
    //初始化互斥信号量
    int ini3 = pthread_mutex_init(&mutex, NULL);
    if (ini3 != 0) {
        printf("mutex init failed \n");
        exit(1);
    }
    //创建生产者线程
    ret = pthread_create(&producer, NULL, produce, NULL);
    if (ret != 0) {
        printf("produce creation failed \n");
        exit(1);
    }
    //创建消费者线程
    ret = pthread_create(&customer, NULL, consume, NULL);
    if (ret != 0) {
        printf("consume creation failed \n");
        exit(1);
    }
    //销毁线程
    pthread_join(producer, NULL);
    pthread_join(customer, NULL);

    exit(0);
}