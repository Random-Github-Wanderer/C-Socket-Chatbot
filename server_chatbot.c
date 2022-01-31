#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> /* srand() */

/* Socket header files */
#include <sys/socket.h>
#include <arpa/inet.h>

#define RHOST argv[1]
#define PORT r % 65535
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {

    srand(time(NULL));
    int socket_fd, new_socket_fd, info_size = sizeof(struct sockaddr_in), r = rand();
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
    server.sin_port = htons(PORT);
    if(argc == 1) {
        server.sin_addr.s_addr = INADDR_ANY;
    } else {
        server.sin_addr.s_addr = inet_addr(RHOST);
    }   

    /* Socket Bind */
    if(bind(socket_fd, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("[ERROR] Binding Socket.\n");

        exit(-1);
    }
    printf("[DEBUG] Bind complete.\n");

    /* Listen */
    listen(socket_fd, 3);
    printf("[DEBUG] Listening on port %d...\n", PORT);

    /* Accept an Incoming Connection */
    printf("[DEBUG] Awaiting Incoming Connections...\n");
    if((new_socket_fd = accept(socket_fd, (struct sockaddr *) &client, (socklen_t *) &info_size)) == -1) {
        printf("[ERROR] Opening new socket.\n");

        exit(-1);
    }
    printf("[DEBUG] New socket successfully opened.\n");
    printf("[DEBUG] Remote Host connected with IP address %s and port %d.\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

    /* Begin Chat */
    printf("| | | |\tSOCKET_CHATBOT\t| | | |\n");
    // send(new_socket_fd, "| | | |\tSOCKET_CHATBOT\t| | | |\n", strlen("| | | |\tSOCKET_CHATBOT\t| | | |\n"), 0);

    while(TRUE) {
        printf("[PENDING]\n");
        if(recv(new_socket_fd, client_message, 100, 0) < 0) {
            printf("[ERROR] Could not receive.\n");
        }
        printf("[CLIENT] %s\n", client_message);

        printf("[SERVER] ");
        scanf(" %[^\n]s", server_message);
        send(new_socket_fd, server_message, strlen(server_message), 0);
        memset(client_message, '\0', strlen(client_message));
        memset(server_message, '\0', strlen(server_message));
    }
}
