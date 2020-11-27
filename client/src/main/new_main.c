#include "client.h"
#include "db.h"

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

static parse_anoyer_result(t_client_data *client_data)
{

}

bool _Noreturn test_anoyer(t_client_data *client_data)
{
    json_t *json =  json_pack("{s:s, s:i}", "type", "ping", "mode", client_data->state);
    json_t *request = NULL;

    while (TRUE)
    {
        sleep(1);
        cmc_log_info("[WORK]");
        char *result = json_dumps(json, 0);
        g_mutex_lock(&client_data->thread.mutex_client);
        write(client_data->server_attr.socket, result, strlen(result));
        request = json_loadfd(client_data->server_attr.socket, JSON_DISABLE_EOF_CHECK, NULL);
        g_mutex_unlock(&client_data->thread.mutex_client);
        cmc_log_info("%s", json_dumps(request, 0));
    }
}

//ToDo: Split all on logical containers and get with gtk_container_foreach()
int main(int argc, char *argv[])
{
    t_client_data *client_data = init_client_data();
    init_connection(client_data);
    init_local_database();
    fill_countries();
    gtk_init(&argc, &argv);

    sqlite3_open("local.db", &client_data->db);

    create_window(MAIN_UI, client_data);

    prepare_signup_page(client_data);
    gtk_widget_show_now(get_widget("login_wnd"));

    g_thread_new("anoyer", (GThreadFunc)test_anoyer, client_data);

    gtk_main();

    g_mutex_clear(&client_data->thread.mutex_interface);
    g_mutex_clear(&client_data->thread.mutex_client);

    system("leaks -q uchat_gui");
    return 0;
}
