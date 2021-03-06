#include "client.h"

static int server_login(t_client_data *client_data)
{
    client_data->server_attr.request = json_object();

    json_t *user = json_object();

    json_object_set_new(user, "nickname", json_string(client_data->user_attr.username));
    json_object_set_new(user, "password", json_string(client_data->user_attr.password));
    json_object_set_new(client_data->server_attr.request, "type", json_string(client_data->type));
    json_object_set_new(client_data->server_attr.request, "user", user);

    send_request(client_data);

//    json_decref(user);

    // FixMe: Temp
    return 1;
}

void login(GtkButton *lwnd_submit_btn, t_client_data *client_data)
{
    client_data->type = LOGIN;
    client_data->user_attr.username = strdup(get_entry_text("lwnd_uname_entry"));
    client_data->user_attr.password = strdup(get_entry_text("lwnd_upass_entry"));

    server_login(client_data);
}
