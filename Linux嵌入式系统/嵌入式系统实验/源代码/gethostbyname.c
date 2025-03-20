#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    struct hostent *host;
    struct in_addr **addr_list;

    if (argc != 2) {
        fprintf(stderr,"Usage: %s hostname\n", argv[0]);
        return 1;
    }

    // 获取主机信息
    if ((host = gethostbyname(argv[1])) == NULL) {
        // 获取失败
        herror("gethostbyname");
        return 1;
    }

    // 将主机的地址列表转换为 IP 地址字符串并打印出来
    addr_list = (struct in_addr **)host->h_addr_list;
    for(int i = 0; addr_list[i] != NULL; i++) {
        printf("%s\n", inet_ntoa(*addr_list[i]));
    }

    return 0;
}
