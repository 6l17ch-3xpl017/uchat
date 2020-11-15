#include "client.h"

static void send_request(t_client_data *client_data)
{
    json_t *json = json_object();
    json_t *chat = json_object();

    json_object_set_new(json, "type", json_string("open_chat"));

    json_object_set_new(chat, "chat_id", json_string("1"));
    json_object_set_new(chat, "user_id", json_string("1"));
    json_object_set_new(json, "chat", chat);

    client_data->server_attr.request = json;

    send_json(client_data);
}

void choose_chat(GtkListBox *box, GtkListBoxRow *row, t_client_data *client_data)
{
    GtkButton *chat = gtk_container_get_children(GTK_CONTAINER(row))->data;
    cmc_log_info(g_object_get_data(G_OBJECT(chat), "chat_id"));

    send_request(client_data);

    cmc_log_info("%s", json_dumps(client_data->server_attr.response, 0));

    json_t *messages = json_object_get(client_data->server_attr.response, "messages");
    json_t *message = NULL;
    for (int i = 0; i < json_array_size(messages); i++) {

        message = json_array_get(messages, i);
        json_t *message_content = json_object_get(message, "msg_content");


        GtkWidget *listbox = get_widget("chat_msg_lst_box");
        GtkWidget *msg = msg_widget_factory(P_MSG, (char *)json_string_value(message_content), client_data->user_attr.username); // ToDo: Request username

        gtk_list_box_insert(GTK_LIST_BOX(listbox), GTK_WIDGET(msg), -1);
        gtk_widget_show_all(listbox);
    }

}