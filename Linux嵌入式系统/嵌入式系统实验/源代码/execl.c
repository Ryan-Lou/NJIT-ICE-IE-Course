#include <stdio.h>
#include <unistd.h>

int main() {
    // 输出当前进程的PID
    printf("The PID of this process is: %d\n", getpid());
    printf("Executing 'ls' command...\n");

    // 调用execl执行/bin/ls命令
    // 第一个参数是命令的完整路径
    // 第二个参数是传递给命令的第一个参数（通常是命令本身的名称）
    // 后面跟随的NULL表示参数列表的结束
    execl("/bin/ls", "ls", NULL);

    // 如果execl调用成功，下面的代码将不会执行
    // 因为当前进程的映像已经被/bin/ls的映像替换
    // 如果出现错误，将会打印以下错误消息
    perror("execl");
    return 1; // 返回非零值表示程序出错
}

