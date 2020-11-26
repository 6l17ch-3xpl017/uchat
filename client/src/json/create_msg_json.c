#include "client.h"

void create_msg_json(gchar *msg_text, t_client_data *client_data)
{
    json_t *json = json_object();
    json_t *msg = json_object();

    json_object_set_new(json, "type", json_string(SEND_MSG));

    json_object_set_new(json, "msg_type", json_string("text"));
    json_object_set_new(msg, "message_content", json_string(msg_text));
    json_object_set_new(msg, "message_owner_id", json_string(client_data->user_attr.user_id));
    json_object_set_new(msg, "message_owner_name", json_string(client_data->user_attr.username));
    json_object_set_new(msg, "chat_id", json_string("1"));
    json_object_set_new(msg, "time", json_integer(1));
    json_object_set_new(json, "message", msg);

    client_data->server_attr.request = json;

    send_request(client_data);
}
