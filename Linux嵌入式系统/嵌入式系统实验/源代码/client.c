#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server;
    char message[BUFFER_SIZE], server_reply[BUFFER_SIZE];

    // 创建socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("创建socket失败");
        return 1;
    }
    puts("Socket创建成功");

    // 准备服务器地址和端口
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // 这里使用本机地址
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("连接失败");
        return 1;
    }
    puts("连接到服务器");

    // 发送一些数据
    printf("输入消息: ");
    fgets(message, BUFFER_SIZE, stdin);

    if (send(sock, message, strlen(message), 0) < 0) {
        perror("发送失败");
        return 1;
    }

    // 接收服务器的响应
    if (recv(sock, server_reply, BUFFER_SIZE, 0) < 0) {
        perror("接收失败");
        return 1;
    }

    puts("服务器响应: ");
    puts(server_reply);

    close(sock);
    return 0;
}
