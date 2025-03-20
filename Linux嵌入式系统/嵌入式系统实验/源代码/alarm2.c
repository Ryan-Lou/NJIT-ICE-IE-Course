#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// 信号处理函数
void handle_sigalrm(int sig) {
    printf("Alarm triggered after 2 seconds!\n");
    // 信号处理完毕后，可以添加额外的操作
}

int main() {
    // 注册SIGALRM的处理器
    signal(SIGALRM, handle_sigalrm);

    // 设置2秒后触发的定时器
    alarm(2);

    printf("Alarm set for 2 seconds.\n");

    // 等待信号到来，这通常会使程序暂停，直到信号处理器被调用
    pause();

    printf("Program will now terminate.\n");

    return 0;
}

