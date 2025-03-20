#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void* client_handler(void* socket_desc) {
    int sock = *(int*)socket_desc;
    char client_message[BUFFER_SIZE];

    // 接收客户端的数据
    ssize_t read_size = recv(sock, client_message, BUFFER_SIZE, 0);
    if (read_size > 0) {
        printf("%s\n", client_message);
        send(sock, "Handler assigned\n", 17, 0);
    } else {
        perror("recv failed");
    }

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
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("bind done\n");

    // 设置服务器地址结构
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // 绑定socket到地址和端口
    if (bind(server_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听socket
    listen(server_fd, 3);
    printf("Waiting for incoming connections...\n");

    // 接受连接
    while ((client_sock = accept(server_fd, (struct sockaddr*)&client, &client_size))) {
        printf("Connection accepted\n");

        new_sock = malloc(sizeof(int));
        *new_sock = client_sock;

        // 为每个客户端创建一个线程
        if (pthread_create(&thread_id, NULL, client_handler, (void*)new_sock) < 0) {
            perror("could not create thread");
            free(new_sock);
        }
    }

    if (client_sock < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

