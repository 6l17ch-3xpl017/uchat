#include "server.h"

void *connection_handler(void *socket_desc) {

    //Get the socket descriptor
    int sock = *(int *) socket_desc;
    int read_size;
    char *message, client_message[2000];
    //Send some messages to the client
    message = "Greetings! I am your connection handler\n";
    write(sock, message, strlen(message));
    message = "Now type something and i shall repeat what you type \n";
    write(sock, message, strlen(message));
    //Receive a message from client
    while ((read_size = recv(sock, client_message, 2000, 0)) > 0) {
        //end of string marker
        client_message[read_size] = '\0';
        //Send the message back to client
        write(sock, client_message, strlen(client_message));

        //clear the message buffer
        memset(client_message, 0, 2000);
    }
    //TODO here add json parse;


    //TODO here add router;

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("reci failed");
    }
    return 0;
}


int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    //----------------------------------------------------

    init_database();

    //----------------------------------------------------

    char str[] = "{\n"
                 "  \"type\": \"sign_in\",\n"
                 "  \"user\": {\n"
                 "    \"nickname\": \"\",\n"
                 "    \"password\": \"12345\",\n"
                 "    \"email\": \"yevgeniia.ks@gmail.com\",\n"
                 "    \"age\": \"29\",\n"
                 "    \"fullname\": \"YK\",\n"
                 "    \"ph_number\": \"098777\",\n"
                 "    \"user_photo\": \"test\",\n"
                 "    \"option\": \"testo\"\n"
                 "  }\n"
                 "}";

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

    check_route(str);
//    return 0;
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

        //
        json_t *data, *sha, *commit, *message, *root;
        json_error_t error;

        root = json_load_file("/test.json",0,&error);
        if(!root)
        {
            fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
            return 1;
        }
    }
    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }
    return 0;
}

