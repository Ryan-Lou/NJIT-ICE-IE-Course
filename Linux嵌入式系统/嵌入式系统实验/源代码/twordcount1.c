#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 线程函数统计单词数量
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
        count++;  // 计数增加
    }
    fclose(fp);  // 关闭文件

    printf("文件 %s 有 %d 个单词\n", filename, count);
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t t1;

    if (argc != 2) {
        printf("使用方法: %s <文件名>\n", argv[0]);
        exit(1);
    }

    pthread_create(&t1, NULL, count_words, (void*)argv[1]);  // 创建线程
    pthread_join(t1, NULL);  // 等待线程完成

    return 0;
}
