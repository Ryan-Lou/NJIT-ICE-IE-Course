#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// 线程函数处理客户端连接
void *handle_client(void *socket_desc) {
    int sock = *(int*)socket_desc;
    char buffer[BUFFER_SIZE];
    int read_size;

    // 接收客户端发送的消息
    while ((read_size = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        // 发送回客户端
        send(sock, buffer, read_size, 0);
    }

    if (read_size == 0) {
        puts("客户端断开连接");
    } else if (read_size == -1) {
        perror("recv失败");
    }

    // 关闭socket
    close(sock);
    free(socket_desc);

    return NULL;
}

int main() {
    int server_fd, client_sock, *new_sock;
    struct sockaddr_in server, client;
    socklen_t client_size = sizeof(struct sockaddr_in);
    pthread_t thread_id;

    // 创建socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("创建socket失败");
        return 1;
    }

    // 准备sockaddr_in结构体
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // 绑定
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("绑定失败");
        return 1;
    }

    // 监听
    listen(server_fd, 3);

    printf("等待客户端连接...\n");

    // 接受客户端连接
    while ((client_sock = accept(server_fd, (struct sockaddr *)&client, &client_size))) {
        printf("连接已建立\n");

        new_sock = malloc(sizeof(int));
        *new_sock = client_sock;

        if (pthread_create(&thread_id, NULL, handle_client, (void*)new_sock) < 0) {
            perror("创建线程失败");
            return 1;
        }
    }

    if (client_sock < 0) {
        perror("接受失败");
        return 1;
    }

    return 0;
}
