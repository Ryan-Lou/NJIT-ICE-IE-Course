#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // 创建新进程
    pid = fork();

    if (pid == 0) {
        // 子进程中
        printf("Child process: PID=%d, Parent's PID=%d\n", getpid(), getppid());
    } else if (pid > 0) {
        // 父进程中
        printf("Parent process: PID=%d, Child's PID=%d\n", getpid(), pid);
    } else {
        // fork失败
        perror("fork");
        return 1;
    }

    return 0; // 父进程和子进程都会执行这条语句
}
