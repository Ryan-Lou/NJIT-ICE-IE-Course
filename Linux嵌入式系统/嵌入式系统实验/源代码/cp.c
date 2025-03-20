#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024  // 定义缓冲区大小

void copy_file(const char *source, const char *destination);

int main(int argc, char *argv[]) {
    if (argc != 3) {  // 确保有足够的参数
        fprintf(stderr, "Usage: %s source_file destination_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    copy_file(argv[1], argv[2]);  // 调用函数来复制文件
    return 0;
}

void copy_file(const char *source, const char *destination) {
    FILE *src, *dest;
    char buf[BUFFER_SIZE];
    size_t bytes;

    // 打开源文件进行读取
    if ((src = fopen(source, "rb")) == NULL) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // 打开目标文件进行写入
    if ((dest = fopen(destination, "wb")) == NULL) {
        perror("Error opening destination file");
        fclose(src);  // 关闭源文件
        exit(EXIT_FAILURE);
    }

    // 读取和写入循环
    while ((bytes = fread(buf, 1, BUFFER_SIZE, src)) > 0) {
        fwrite(buf, 1, bytes, dest);
    }

    // 关闭文件
    fclose(src);
    fclose(dest);
}
