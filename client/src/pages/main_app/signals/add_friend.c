#include "client.h"

int add_new_chat(t_client_data *client_data)
{
    GtkWidget *chats_list = get_widget("hp_chats");
    gtk_list_box_insert(GTK_LIST_BOX(chats_list), create_chat_widget(client_data->server_attr.response), -1);
    gtk_widget_show_all(chats_list);
    return 1;
}

static void make_request_json(char *username, t_client_data *client_data)
{
    json_t *json = json_object();

    json_object_set(json, "type", json_string("new_chat"));
    json_object_set(json, "self_name", json_string(client_data->user_attr.username));
    json_object_set(json, "self_id", json_string(client_data->user_attr.user_id));
    json_object_set(json, "user_name", json_string(username));

    client_data->server_attr.request = json;

    send_request(client_data);
}

gboolean add_friend(GtkEntry *entry, GdkEventKey *event, t_client_data *client_data)
{
    if (event->keyval == GDK_KEY_Return)
    {
        client_data->type = NEW_CHAT;
        char *friend_name = strndup(gtk_entry_get_text(entry), strlen(gtk_entry_get_text(entry)));
        make_request_json(friend_name, client_data);
        mx_strdel(&friend_name);
    }

    return FALSE;
}