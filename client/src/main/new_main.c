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

static void parse_annoyer_result(t_client_data *client_data)
{
    g_mutex_lock(&client_data->thread.mutex_interface);

    GtkWidget *listbox = get_widget("cm_lbox");

    json_t *msg_array = json_object_get(client_data->server_attr.response, "messages");
    json_t *msg_obj;
    json_t *msg_id;
    json_t *last_author;
    char *s_last_author;

    cmc_log_info("%s", json_dumps(msg_array, 0));

    for (int i = 0; i < json_array_size(msg_array); i++)
    {
        msg_obj = json_array_get(msg_array, i);
        msg_id = json_object_get(msg_obj, "msg_id");

        cmc_log_info("%s", json_string_value(msg_id));

        msg_obj = json_array_get(msg_array, i);

        gtk_list_box_insert(GTK_LIST_BOX(listbox), create_msg_widget(msg_obj, s_last_author, client_data), -1);

        last_author = json_object_get(msg_obj, "author_name");
        s_last_author = strdup(json_string_value(last_author));
        gtk_widget_show_all(listbox);

    }

    g_mutex_unlock(&client_data->thread.mutex_interface);
}

bool _Noreturn test_annoyer(t_client_data *client_data)
{
    json_t *request = NULL;
    json_t *json;
    int status = 0;

    while (TRUE)
    {
        sleep(1);
        cmc_log_info("[WORK]");

        if (client_data->state > 0)
            json = json_pack("{s:s, s:i, s:s}", "type", "ping", "mode", client_data->state, "msg_id", client_data->state_data);
        else
            json = json_pack("{s:s, s:i}", "type", "ping", "mode", client_data->state);

        char *result = json_dumps(json, 0);

        if(result)
        {
            g_mutex_lock(&client_data->thread.mutex_client);
            write(client_data->server_attr.socket, result, strlen(result));
            request = json_loadfd(client_data->server_attr.socket, JSON_DISABLE_EOF_CHECK, NULL);
            g_mutex_unlock(&client_data->thread.mutex_client);
        }
        json_unpack(request, "{s:i}", "status", &status);

        if (status is 2 and client_data->state > 0)
        {
            client_data->server_attr.response = request;
            gdk_threads_add_idle((GSourceFunc)parse_annoyer_result, client_data);
        }

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


    g_thread_new("annoyer", (GThreadFunc)test_annoyer, client_data);

    gtk_main();

    g_mutex_clear(&client_data->thread.mutex_interface);
    g_mutex_clear(&client_data->thread.mutex_client);

    system("leaks -q uchat_gui");
    return 0;
}
