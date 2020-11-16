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

static const char *get_username(const char *id, t_client_data *client_data)
{
    json_t *users = json_object_get(client_data->server_attr.response, "receivers");
    json_t *user = NULL;

    for (int i = 0; i < json_array_size(users); i++)
    {
        user = json_array_get(users, i);
        json_t *user_id = json_object_get(user, "users_id");

        if (strcmp((char *)json_string_value(user_id), id) is 0)
            return json_string_value(json_object_get(user, "username"));

    }
    cmc_log_fatal("Cannot find user | user_id = %s", id);
}

void choose_chat(GtkListBox *box, GtkListBoxRow *row, t_client_data *client_data)
{
    GtkButton *chat = gtk_container_get_children(GTK_CONTAINER(row))->data;
    cmc_log_info(g_object_get_data(G_OBJECT(chat), "chat_id"));

    send_request(client_data);

    cmc_log_info("%s", json_dumps(client_data->server_attr.response, 0));

    json_t *messages = json_object_get(client_data->server_attr.response, "messages");
    json_t *message = NULL;


    /* TEMP CODE */
    char *last_author = NULL;


    for (int i = 0; i < json_array_size(messages); i++) {

        message = json_array_get(messages, i);
        json_t *message_content = json_object_get(message, "msg_content");
        json_t *author = json_object_get(message, "author");

        if (last_author == NULL)
        {
            last_author = (char *)json_string_value(author);
        }



        GtkWidget *listbox = get_widget("chat_msg_lst_box");

        GtkWidget *msg = msg_widget_factory(strcmp(json_string_value(author), last_author) == 0 ? 1 : 2, (char *)json_string_value(message_content),
                                                   (char *)get_username(json_string_value(author), client_data)); // ToDo: Request username

       strcmp(json_string_value(author), last_author) == 0 ? 0 : (last_author = (char *)json_string_value(author));

        gtk_list_box_insert(GTK_LIST_BOX(listbox), GTK_WIDGET(msg), -1);
        gtk_widget_show_all(listbox);
    }

}