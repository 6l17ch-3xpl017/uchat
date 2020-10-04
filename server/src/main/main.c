//#include "server.h"
//
//void *connection_handler(void *socket_desc) {
//    //Get the socket descriptor
//    int sock = *(int *) socket_desc;
//    int read_size = 1;
//    char client_message[2000];
//
////    t_use_mutex *thread_mutex = (t_use_mutex *) socket_desc;
//    for (;;) {
////        pthread_mutex_lock(&(thread_mutex->mutex));
//        read(sock, client_message, sizeof(client_message));
////      client exit
//        if ((strncmp(client_message, "exit", 4)) == 0) {
//            printf("Client Exit...\n");
//            read_size = 0;
//        }
////        check_route(client_message);
//            puts(client_message);
////      client disconnected
//        if (read_size == 0) {
//            puts("Client disconnected");
//            fflush(stdout);
//            return 0;
//        }
////        pthread_mutex_unlock(&(thread_mutex->mutex));
//    }
//}
//
//int main(int argc, char *argv[]) {
//    (void) argc;
//    (void) argv;
//    int socket_desc, client_sock, c;
//    struct sockaddr_in server, client;
//    unsigned short port = 5000;
//
//    //Prepare the sock_address_in structure
//    server.sin_family = AF_INET;
//    server.sin_addr.s_addr = inet_addr("127.0.0.1");
//    server.sin_port = htons(port);
//
//    //Create socket
//    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
//    if (socket_desc == -1)
//        printf("Could not create socket");
//
//    puts("Socket created");
//    //Bind
//    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
//        //print the error message
//        perror("bind failed. Error");
//        return 1;
//    }
//    puts("bind done");
//    //Listen
//    listen(socket_desc, 3);
//    //Accept and incoming connection
//    puts("Waiting for incoming connections...");
//    c = sizeof(struct sockaddr_in);
//    //create and connect threads and mutex
//    pthread_t thread_id;
////    t_use_mutex thread_mutex;
//
////    pthread_mutex_init(&(thread_mutex.mutex), NULL);
//
//    while ((client_sock = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c))) {
//        puts("Connection accepted");
//        if (!pthread_create(&thread_id, NULL, connection_handler, (void *) &client_sock)) {
//            perror("could not create thread");
//            return 1;
//        }
//        //Now join the thread , so that we don't terminate before the thread
//        //pthread_join( thread_id , NULL);
//        puts("Handler assigned");
//    }
//    if (client_sock < 0) {
//        perror("accept failed");
//        return 1;
//    }
//}


#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
//#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>

char client_message[2000];
char buffer[1024];

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void *socketThread(void *arg) {
    int newSocket = *((int *) arg);
    recv(newSocket, client_message,2000, 0);
    // Send message to the client socket
    pthread_mutex_lock(&lock);
    char *message = malloc(sizeof(client_message) + 20);
    strcpy(message,"Hello Client : ");
    strcat(message, client_message);
    strcat(message,"\n");
    strcpy(buffer, message);
    free(message);
    pthread_mutex_unlock(&lock);
    sleep(1);
    send(newSocket, buffer,13, 0);
    printf("Exit socketThread \n");
    close(newSocket);
    pthread_exit(NULL);
}

int main() {
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    //Create the socket.
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    // Configure settings of the server address struct
    // Address family = Internet
    serverAddr.sin_family = AF_INET;
    //Set port number, using htons function to use proper byte order
    serverAddr.sin_port = htons(7799);
    //Set IP address to localhost
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //Set all bits of the padding field to 0
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Bind the address struct to the socket
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    //Listen on the socket, with 40 max connection requests queued
    if (listen(serverSocket, 50) == 0)
        printf("Listening\n");
    else
        printf("Error\n");
    pthread_t tid[60];
    int i = 0;
    while (1) {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
        //for each client request creates a thread and assign the client request to it to process
        //so the main thread can entertain next request
        if (pthread_create(&tid[i++], NULL, socketThread, &newSocket) != 0)
            printf("Failed to create thread\n");
        if (i >= 50) {
            i = 0;
            while (i <50) {
                pthread_join(tid[i++], NULL);
            }
            i = 0;
        }
    }
//    return 0;
}
