#include "server.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void mutex_lock_unlock(void) {

}
//--------------------------------------------------------
static t_chat *chat_struct_filling_with_null() {
    t_chat *Chat = malloc(sizeof(t_chat));
    Chat->chat_name = "1";
    Chat->chat_photo = NULL;
    Chat->chat_id = NULL;
    Chat->option = NULL;
    Chat->admin_id = "1";
    return Chat;
}
//--------------------------------------------------------

//static void InitializeSSL()
//{
//    SSL_load_error_strings();
//    SSL_library_init();
//    OpenSSL_add_all_algorithms();
//}
//
//static void DestroySSL()
//{
//    ERR_free_strings();
//    EVP_cleanup();
//}

//static void ShutdownSSL()
//{
//    SSL_shutdown(cSSL);
//    SSL_free(cSSL);
//}


static void *socketThread(void *arg) {
    int newSocket = *((int *) arg);
    char client_message[20000];
    int status;
    t_thread_sockuser *thread = NULL;

    thread = (t_thread_sockuser *) malloc(sizeof(t_thread_sockuser));
    thread->socket = newSocket;

    for (;;) {
        read(newSocket, client_message, sizeof(client_message));

//      router
        status = check_route(client_message, thread);
        puts(client_message); // print json

//      client disconnected
        if (status == unknown_error) {
            puts("Client disconnected");
            fflush(stdout);
            close(thread->socket);
            free(thread);
            return 0;
        }
    }
}

static void server_async_create() {
    int serverSocket, newSocket, i = 0;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

//    SSL_CTX *sslctx;
//    SSL *cSSL;

//    InitializeSSL();
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    init_database();
//--------------------------------------------------------
//    add_chat_to_db(chat_struct_filling_with_null());
//--------------------------------------------------------

    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (listen(serverSocket, 50) == 0)
        printf("Listening\n");
    else
        printf("Error\n");
    pthread_t tid[60];
    while (1) {
        addr_size = sizeof serverStorage;
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
        if (pthread_create(&tid[i++], NULL, socketThread, &newSocket) != 0)
            printf("Failed to create thread\n");
        if (i >= 50) {
            i = 0;
            while (i < 50)
                pthread_join(tid[i++], NULL);
            i = 0;
        }
    }
}

static void skeleton_daemon() {
    pid_t pid;
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);
    if (setsid() < 0)
        exit(EXIT_FAILURE);
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);
    umask(0);
    chdir("/");
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
        close(x);
    openlog("firstdaemon", LOG_PID, LOG_DAEMON);
}



int main() {
//    skeleton_daemon();

//    while (1) {
//        //TODO: Insert daemon code here.
    server_async_create();
//------------------------------
//    t_thread_sockuser *thread = NULL;
//    char *send_msg;
//    int newSocket = *(int*)5;

//    thread = (t_thread_sockuser *) malloc(sizeof(t_thread_sockuser));
//    thread->socket = 5;
//    init_database();
//    add_chat_to_db(chat_struct_filling_with_null());
//    json_t *message = json_object();
//    json_t *json = json_object();
//    json_object_set_new(message, "chat_id", json_string("1"));
//    json_object_set_new(message, "chat_type", json_string("public"));
//    json_object_set_new(message, "chat_name", json_string("chatik"));
//    json_object_set_new(message, "admin_id", json_string("1"));
//    json_object_set_new(message, "message_id", json_string("1"));
//    json_object_set_new(message, "message_content", json_string("Second message"));
//    json_object_set_new(message, "message_owner_id", json_string("1"));
//    json_object_set_new(message, "type", json_string("text"));
//    json_object_set_new(message, "time", json_string("2020"));
//
//    json_object_set_new(json, "type", json_string("send_message"));
//    json_object_set_new(json, "message", message);
//
//    send_msg = json_dumps(json, 0);
//    check_route(send_msg, thread);
//------------------------------


//    }

}
