#include "server.h"

static t_chat *chat_struct_filling_with_null() {
    t_chat *Chat = malloc(sizeof(t_chat));
    Chat->chat_name = "Ukraine";
    Chat->chat_photo = NULL;
    Chat->chat_id = NULL;
    Chat->option = NULL;
    Chat->admin_id = "1";
    Chat->next = NULL;
    Chat->user_in_chat = malloc(sizeof(t_user));
    Chat->user_in_chat->next = NULL;
    return Chat;
}

static void ev_handler(struct ns_connection *nc, int ev, void *p) {
    int size = 1048576;
    setsockopt(nc->sock, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

    struct iobuf *io = &nc->recv_iobuf;
    char *income_json = NULL;
    char *buff = mx_strnew(2048);
    if (ev == NS_RECV)
    {
        income_json = strndup(io->buf, io->len);

        check_route(income_json, nc);
        iobuf_remove(io, io->len);
        free(income_json);
    }
    else if (ev == NS_ACCEPT)
    {
        printf("A\n");
    }
    else if (ev == NS_CLOSE)
    {
        puts("X\n");
    }
}

static void connecting_to_port(char *port, struct ns_mgr *mgr) {
    int temp = atoi(port);

    if (temp != 0) {
        ns_bind(mgr, port, ev_handler, NULL);
        printf("Starting server on port: %s\n", port);
    }
    else
        exit(0);
}

static void do_main_work(int argc, char *argv[])
{
    struct ns_mgr mgr;
    char *chat_name = "Ukraine";

    ns_mgr_init(&mgr, NULL);
    init_database();

    if (get_chat_by_id(chat_name) == NULL)
        add_chat_to_db(chat_struct_filling_with_null());

    if (argc == 2)
        connecting_to_port(argv[1], &mgr);
    else
    {
        write(2, "usage: ./uchat_server [port]", strlen("usage: ./uchat_server [port])"));
        exit(0);
    }

    for (;;)
        ns_mgr_poll(&mgr, 1000);
}


int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        write(2, "usage: ./uchat_server [port]", strlen("usage: ./uchat_server [port])"));
        exit(0);
    }

    pid_t process_id = 0;
    pid_t sid = 0;
    // Create child process
    process_id = fork();
    // Indication of fork() failure
    if (process_id < 0)
    {
        printf("fork failed!\n");
    // Return failure in exit status
        exit(1);
    }
    // PARENT PROCESS. Need to kill it.
    if (process_id > 0)
    {
        printf("process_id of child process %d \n", process_id);
    // return success in exit status
        exit(0);
    }

    umask(0);
    sid = setsid();
    if(sid < 0)
        exit(1);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    do_main_work(argc, argv);
    return (0);
}
