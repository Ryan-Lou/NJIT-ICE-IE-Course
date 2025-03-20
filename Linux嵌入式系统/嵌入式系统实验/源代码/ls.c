#include <stdio.h>
#include <dirent.h>  // 包含目录操作的函数定义
#include <stdlib.h>

void list_files(const char *dir);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // 如果没有提供目录，默认为当前目录
        list_files(".");
    } else {
        // 否则，列出指定的目录
        list_files(argv[1]);
    }
    return 0;
}

void list_files(const char *dir) {
    struct dirent *entry;
    DIR *dp;

    // 尝试打开目录
    dp = opendir(dir);
    if (dp == NULL) {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }

    // 读取目录中的每个条目
    while ((entry = readdir(dp)) != NULL) {
        // 打印条目的名字
        printf("%s\n", entry->d_name);
    }

    // 关闭目录流
    closedir(dp);
}
