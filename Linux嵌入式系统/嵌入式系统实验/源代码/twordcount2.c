#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 5  // 定义最大线程数

int total_words = 0;  // 定义全局变量存储总单词数
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // 初始化互斥锁

// 线程函数来统计单词数量
void* count_words(void* f) {
    char* filename = (char*)f;
    FILE* fp;
    int count = 0;
    char word[1024];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("文件打开失败");
        return NULL;
    }

    while (fscanf(fp, "%1023s", word) == 1) {  // 读取单词
        count++;
    }
    fclose(fp);  // 关闭文件

    pthread_mutex_lock(&mutex);  // 上锁
    total_words += count;  // 更新全局变量
    pthread_mutex_unlock(&mutex);  // 解锁

    printf("文件 %s 有 %d 个单词\n", filename, count);
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t threads[MAX_THREADS];
    int num_threads = argc - 1;

    if (argc < 2) {
        printf("使用方法: %s <文件1> <文件2> ... <文件N>\n", argv[0]);
        exit(1);
    }

    // 创建多个线程来统计单词
    for (int i = 0; i < num_threads && i < MAX_THREADS; i++) {
        if(pthread_create(&threads[i], NULL, count_words, (void*)argv[i + 1])) {
            perror("线程创建失败");
            return 1;
        }
    }

    // 等待所有线程完成
    for (int i = 0; i < num_threads && i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("总单词数: %d\n", total_words);

    return 0;
}
