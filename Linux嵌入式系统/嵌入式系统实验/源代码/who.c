#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

void show_info(struct utmp *utbufp);

int main() {
    struct utmp current_record;  // 用于存储信息的结构
    int utmpfd;                  // 文件描述符
    int reclen = sizeof(current_record);

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);  // UTMP_FILE 是包含用户登录记录的文件
        exit(1);
    }

    while (read(utmpfd, &current_record, reclen) == reclen)
        show_info(&current_record);
    close(utmpfd);
    return 0;  // 程序成功退出
}

void show_info(struct utmp *utbufp) {
    if (utbufp->ut_type != USER_PROCESS)  // 只关心用户进程
        return;

    printf("%-8.8s", utbufp->ut_name);  // 登录名
    printf(" ");                        // 空格分隔
    printf("%-8.8s", utbufp->ut_line);  // tty
    printf(" ");                        // 空格分隔
    printf("%10ld", (long)utbufp->ut_time); // 登录时间
    printf(" ");                             // 空格分隔
#ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);  // 主机名
#endif
    printf("\n");  // 换行符
}

