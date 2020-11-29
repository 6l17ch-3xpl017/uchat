#include "client.h"

void create_msg_json(gchar *msg_text, gchar *msg_type, t_client_data *client_data)
{
    json_t *json = json_object();
    json_t *msg = json_object();

    char *str_time = mx_strnew(256);
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);
    strftime(str_time, 256, "%r", ptm);

    json_object_set_new(json, "type", json_string(SEND_MSG));

    json_object_set_new(json, "msg_type", json_string(msg_type));
    json_object_set_new(msg, "message_content", json_string(msg_text));
    json_object_set_new(msg, "message_owner_id", json_string(client_data->user_attr.user_id));
    json_object_set_new(msg, "message_owner_name", json_string(client_data->user_attr.username));
    json_object_set_new(msg, "chat_id", json_string(mx_itoa(client_data->state)));
    json_object_set_new(msg, "time", json_string(str_time));
    json_object_set_new(msg, "type", json_string(msg_type));
    json_object_set_new(json, "message", msg);

    client_data->server_attr.request = json;

    send_request(client_data);
}
