#include "server.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void mutex_lock_unlock(void) {

}

static void *socketThread(void *arg) {
    int newSocket = *((int *) arg);
    char client_message[20000];
    int status;
    t_thread_sockuser *thread = NULL;

    thread = (t_thread_sockuser*)malloc(sizeof(t_thread_sockuser));
    thread->socket = newSocket;
    for (;;) {
        read(newSocket, client_message, sizeof(client_message));

//      router
        status = check_route(client_message, thread);
        puts(client_message);

//      client disconnected
        if (status == unknown_error) {
            puts("Client disconnected");
            fflush(stdout);
            free(thread);
            return 0;
        }
    }
}

static void server_async_create() {
    int serverSocket, newSocket, i;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
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
//        syslog(LOG_NOTICE, "First daemon started.");
    server_async_create();
//        sleep(20);
//        break;
//    }
//
//    syslog(LOG_NOTICE, "First daemon terminated.");
//    closelog();
//
//    return EXIT_SUCCESS;

}
