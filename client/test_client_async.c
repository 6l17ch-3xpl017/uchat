//#include<stdio.h>
//#include<sys/socket.h>
//#include<netinet/in.h>
//#include<string.h>
//#include<arpa/inet.h>
//#include<stdlib.h>
//#include<fcntl.h> // for open
//#include<unistd.h> // for close
//#include<pthread.h>
//
//void *cientThread(void *arg) {
//    printf("In thread\n");
//    char message[1000];
//    char buffer[1024];
//    int clientSocket;
//    struct sockaddr_in serverAddr;
//    socklen_t addr_size;
//// Create the socket.
//    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
////Configure settings of the server address
//// Address family is Internet
//    serverAddr.sin_family = AF_INET;
////Set port number, using htons function
//    serverAddr.sin_port = htons(7799);
////Set IP address to localhost
//    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
////Connect the socket to the server using the address
//    addr_size = sizeof serverAddr;
//    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
//    strcpy(message, "Hello");
//    if (send(clientSocket, message, strlen(message), 0) < 0) {
//        printf("Send failed\n");
//    }
////Read the message from the server into the buffer
//    if (recv(clientSocket, buffer, 1024, 0) < 0) {
//        printf("Receive failed\n");
//    }
////Print the received message
//    printf("Data received: %s\n", buffer);
//    close(clientSocket);
//    pthread_exit(NULL);
//}
//
//int main() {
//    int i = 0;
//    pthread_t tid[51];
//    while (i < 50) {
//        if (pthread_create(&tid[i], NULL, cientThread, NULL) != 0)
//            printf("Failed to create thread\n");
//        i++;
//    }
//    sleep(20);
//    i = 0;
//    while (i < 50) {
//        pthread_join(tid[i++], NULL);
//        printf("%d:\n", i);
//    }
//    return 0;
//}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h> // for close


#define MAX 80
#define PORT 5000
#define SA struct sockaddr

void func(int sockfd) {
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        char buff[] = "{\n"
                      "  \"size\": \"100\",\n"
                      "  \"type\": \"sign_up\",\n"
                      "  \"user\": {\n"
                      "    \"nickname\": \"illia\",\n"
                      "    \"password\": \"123asd\",\n"
                      "    \"email\": \"test@test.test\",\n"
                      "    \"age\": \"18\",\n"
                      "    \"fullname\": \"illiash\",\n"
                      "    \"ph_number\": \"0983303840\",\n"
                      "    \"user_photo\": \"101010101\",\n"
                      "    \"option\": \"test\"\n"
                      "  }\n"
                      "}\0";

//        n = 0;
//        while ((buff[n++] = getchar()) != '\n')
//            ;
        write(sockfd, buff, strlen(buff));
//        bzero(buff, sizeof(buff));
//        read(sockfd, buff, sizeof(buff));
//        printf("From Server : %s", buff);
//        if ((strncmp(buff, "exit", 4)) == 0) {
//            printf("Client Exit...\n");
//            break;
    }
}

int main() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    } else
        printf("connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}