#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define MAX_PIDS 10
#define TEN_MILLION 10000000L

sem_t semlock;  // 定义信号量

void worker(int i, void *arg) {
    char buffer[BUF_SIZE];
    char *c;
    sem_t *semlckp;
    struct timespec sleeptime;

    semlckp = (sem_t *) arg;

    sleeptime.tv_sec = 0;
    sleeptime.tv_nsec = TEN_MILLION;

    snprintf(buffer, BUF_SIZE, "This is process %ld\n", (long)getpid());
    c = buffer;

    while (*c != '\0') {
        fputc(*c, stderr); // 逐字符输出
        c++;
        nanosleep(&sleeptime, NULL);
    }

    if(sem_post(semlckp) == -1) { // 信号量V操作
        fprintf(stderr, "Thread failed to unlock semaphore\n");
        return;
    }
}

int main(int argc, char *argv[]) {
    int error;
    int i;
    int n;
    pthread_t pids[MAX_PIDS];

    if (argc != 2) { // 检查命令行参数的数量
        fprintf(stderr, "Usage: %s numprocesses\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    sem_init(&semlock, 0, 1); // 初始化信号量

    for (i = 0; i < n; i++) { // 创建线程
        error = pthread_create(&pids[i], NULL, (void *(*)(void *))worker, (void *)&semlock);
        if (error != 0) {
            fprintf(stderr, "Failed to create thread: %d\n", error);
            sem_destroy(&semlock);
            exit(1);
        }
    }

    for (i = 0; i < n; i++) { // 等待所有线程完成
        pthread_join(pids[i], NULL);
    }

    sem_destroy(&semlock); // 销毁信号量
    return 0;
}
