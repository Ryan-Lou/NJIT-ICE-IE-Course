#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // 创建子进程
    pid = fork();

    if (pid < 0) {
        // fork失败
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // 子进程
        printf("This is the child process. My PID is %d and my parent's PID is %d.\n", getpid(), getppid());
    } else {
        // 父进程
        printf("This is the parent process. My PID is %d and my child's PID is %d.\n", getpid(), pid);
    }

    return 0; // 父子进程都会执行这一行
}
