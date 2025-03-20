#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;  // 定义互斥锁

int main() {
    // 初始化互斥锁
    pthread_mutex_init(&lock, NULL);

    printf("按下 Enter 键来锁定...\n");
    getchar();  // 等待用户按下 Enter 键

    // 加锁
    pthread_mutex_lock(&lock);
    printf("已锁定！\n");

    printf("再次按下 Enter 键来解锁...\n");
    getchar();  // 等待用户再次按下 Enter 键

    // 解锁
    pthread_mutex_unlock(&lock);
    printf("已解锁！\n");

    // 销毁互斥锁
    pthread_mutex_destroy(&lock);

    return 0;
}
