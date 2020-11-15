#include "client.h"

// ToDo: Free memmory
static t_client_data *init_client_data(void)
{
    t_client_data *client_data = calloc(1, sizeof(t_client_data));

    char *status = NULL;
    char *type = NULL;

    client_data->gtk_attr.error = NULL;

    return client_data;
}

static void init_connection(t_client_data *client_data)
{
    cmc_log_info("[Trying connect to server]");

    struct sockaddr_in servaddr;

    cmc_log_info("[Trying to create a socket]");

    // ToDo: Add messages to .h
    check_error((client_data->server_attr.socket = socket(AF_INET, SOCK_STREAM, 0)) == -1,
                "[Socket successfully created]", strerror(errno))

    memset(&servaddr, 0, sizeof(servaddr));

    //ToDo: add auto ip and port assign and log output
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(7777);

    cmc_log_info("[Trying connect server socket to client socket]");

    check_error(connect(client_data->server_attr.socket, (SA*)&servaddr, sizeof(servaddr)) != 0,
                "[Connected to server]", strerror(errno))
}

//ToDo: Split all on logical containers and get with gtk_container_foreach()
int main(int argc, char *argv[])
{
    t_client_data *client_data = init_client_data();
    init_connection(client_data);
    gtk_init(&argc, &argv);

    create_window(TEST_PAGE, client_data);
    gtk_widget_show_now(get_widget("login_window"));

    gtk_main();
    system("leaks -q uchat_gui");
    return 0;

//    json_t *array = json_array();
//    char **msg = calloc(5, sizeof(char *));
//
//    for (int i = 0; i <= 5; i++)
//        msg[i] = calloc(32, sizeof(char));
//
//    json_array_append(array, json_string("Hello"));
//    json_array_append_new(array, json_string("Hello1"));
//    json_array_append_new(array, json_string("Hello2"));
//    json_array_append_new(array, json_string("Hello3"));
//    json_array_append_new(array, json_string("Hello4"));
//
//    int result = json_unpack(array, "[s!]", msg);
//
//    for (int j = 0; j <= 5; j++)
//        printf("%s", msg[j]);

}