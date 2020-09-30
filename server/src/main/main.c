#include "server.h"

void *connection_handler(void *socket_desc) {

    //Get the socket descriptor
    int sock = *(int *) socket_desc;
    int read_size = 1;
    char client_message[2000];
    for (;;) {
        read(sock, client_message, sizeof(client_message));
//      client exit
        if ((strncmp(client_message, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            read_size = 0;
        }
        puts(client_message);
        check_route(client_message);

//      client disconnected
        if (read_size == 0) {
            puts("Client disconnected");
            fflush(stdout);
            return 0;
        }
    }

}


int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;

    //Prepare the sock_address_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5000);

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
        printf("Could not create socket");

    puts("Socket created");
    //Bind
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
    //Listen
    listen(socket_desc, 3);
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    pthread_t thread_id;

    while ((client_sock = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c))) {
        puts("Connection accepted");
        if (pthread_create(&thread_id, NULL, connection_handler, (void *) &client_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
        //Now join the thread , so that we don't terminate before the thread
        //pthread_join( thread_id , NULL);
        puts("Handler assigned");
    }
    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }
}
