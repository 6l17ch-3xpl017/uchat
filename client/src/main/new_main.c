#include "client.h"

// ToDo: Free memmory
static t_client_data *init_client_data(void)
{
    t_client_data *client_data = calloc(1, sizeof(t_client_data));

    client_data->status = NULL;
    client_data->type = NULL;
    client_data->status = NO_STATE;

    client_data->gtk_attr.error = NULL;
    client_data->gtk_attr.provider = gtk_css_provider_new();

    g_mutex_init(&client_data->thread.mutex_interface);
//    client_data->thread.pool = calloc(sizeof(struct cmc_thread *), 10);
//    client_data->gtk_attr.context = NULL;

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

    create_window(MAIN_UI, client_data);

    prepare_signup_page(client_data);
    gtk_widget_show_now(get_widget("login_wnd"));

    gtk_main();

    g_mutex_clear(&client_data->thread.mutex_interface);

    system("leaks -q uchat_gui");
    return 0;

//    int fo = open("../client/resources/countries", O_RDONLY);
//    int fn = open("../client/resources/new_countries.txt", O_WRONLY);
//
//    char buf[2];
//    buf[1] = '\0';
//
//    char *result = calloc(sizeof(char), 125);
//    char *flag_link = calloc(sizeof(char), 50);
//
//    strcpy(flag_link, "https://ipgeolocation.io/static/flags/");  //ag_64.png
//
//    char code[4];
//    code[3] = '\0';
//
//    for (int i = 0; i < 241; i++)
//    {
//        read(fo, &code, 3);
//
//        while (read(fo, &buf, 1)) {
//            if (buf[0] is '\n')
//                break;
//
//            strcat(result, buf);
//        }
//
//        strcat(result, "|");
//
//        strcat(result, "https://ipgeolocation.io/static/flags/");
//
//        result[strlen(result)] = code[0] + 32;
//        result[strlen(result)] = code[1] + 32;
//
//        strcat(result, "_64.png\n");
//
//        write(fn, result, strlen(result));
//        mx_strdel(&result);
//        result = calloc(sizeof(char), 125);
//    }
//
//    close(fn);
//    close(fo);
//
//    return 0;
}
