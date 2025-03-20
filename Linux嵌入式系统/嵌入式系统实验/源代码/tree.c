#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void list_directory(const char *dir_name, int indent);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("%s\n", argv[1]);  // 打印根目录
    list_directory(argv[1], 0);  // 从根目录开始列出文件
    return 0;
}

void list_directory(const char *dir_name, int indent) {
    DIR *dir;
    struct dirent *entry;
    char path[1024];

    if (!(dir = opendir(dir_name))) {
        fprintf(stderr, "Cannot open directory: %s\n", dir_name);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {  // 如果是目录
            char *name = entry->d_name;
            if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
                continue;  // 忽略. 和..
            snprintf(path, sizeof(path), "%s/%s", dir_name, name);
            printf("%*s[%s]\n", indent, "", name);  // 打印目录名
            list_directory(path, indent + 2);  // 递归调用
        } else {
            printf("%*s- %s\n", indent, "", entry->d_name);  // 打印文件名
        }
    }
    closedir(dir);
}
