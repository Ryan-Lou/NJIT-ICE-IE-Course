#include <stdlib.h>

int main() {
    // 无限循环
    while (1) {
        // 每次循环分配一些内存
        int *leak = malloc(sizeof(int) * 1024);

        // 假设程序在这里做了一些工作，但忘记释放内存
        // ... （省略代码）

        // 正确的做法是在不需要内存时释放它：
        // free(leak);  // 但这行被故意省略以造成内存泄漏
    }

    // 实际上，程序永远不会到达这里
    return 0;
}
