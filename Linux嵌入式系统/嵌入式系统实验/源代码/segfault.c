#include <stdio.h>

int main() {
    int *ptr = NULL; // 初始化指针为NULL
    printf("A segmentation fault will occur now.\n");
    *ptr = 0;       // 尝试写入一个NULL指针，这将触发段错误
    return 0;
}
