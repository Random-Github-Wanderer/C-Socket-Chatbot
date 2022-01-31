#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Socket header files */
#include <sys/socket.h>
#include <arpa/inet.h>

#define RHOST argv[1]
#define PORT atoi(argv[2])
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {

    int socket_fd, info_size = sizeof(struct sockaddr_in);
    struct sockaddr_in server, client;
    char server_message[100], client_message[100];

    /* Socket Creation */
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1) {
        printf("[ERROR] Opening Socket.\n");
        
        exit(-1);
    }
    printf("[DEBUG] Socket opened.\n");

    /* Server sockaddr_in Structure */
    server.sin_family = AF_INET;
    if(argc < 2) {
        printf("Usage : %s RHOST [IPv4 Address] Port No. [int]\n", argv[0]);
        exit(-1);
    } else {
        server.sin_addr.s_addr = inet_addr(RHOST);
        server.sin_port = htons(PORT);
    }

    /* Connect to remote server */
    if(connect(socket_fd, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("[ERROR] Could not connect\n");
        exit(-1);
    }

    while(TRUE) {
        printf("[CLIENT] ");
        scanf(" %[^\n]s", client_message);
        send(socket_fd, client_message, strlen(client_message), 0);
        printf("[PENDING]\n");

        recv(socket_fd, server_message, 100, 0);
        printf("[SERVER] %s\n", server_message);

        memset(client_message, '\0', strlen(client_message));
        memset(server_message, '\0', strlen(server_message));
    }
}