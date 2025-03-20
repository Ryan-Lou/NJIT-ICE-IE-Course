#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 线程的运行函数
void* say_hello(void* num) {
    int* th_num = (int*)num;
    printf("Hello from thread %d!\n", *th_num);
    free(num);
    return NULL;
}

int main() {
    int threads_count = 5;  // 创建5个线程
    pthread_t threads[threads_count];

    for (int i = 0; i < threads_count; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        // 创建线程，每个线程都运行say_hello函数
        if (pthread_create(&threads[i], NULL, say_hello, a) != 0) {
            perror("Failed to create thread");
        }
    }

    // 等待所有线程完成
    for (int i = 0; i < threads_count; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");

    return 0;
}
