#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server;
    char message[BUFFER_SIZE], server_reply[BUFFER_SIZE];

    // 创建socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    // 连接到服务器
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected\n");

    // 向服务器发送数据
    strcpy(message, "2901FFFFFFFFFFFFFFFFFFFF\n");
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }

    // 接收服务器的回复
    if (recv(sock, server_reply, BUFFER_SIZE, 0) < 0) {
        perror("recv failed");
        exit(EXIT_FAILURE);
    }

    printf("%s", server_reply);

    close(sock);
    return 0;
}
