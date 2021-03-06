#include "client.h"

static void prepare_request(GtkListBoxRow *chat_id, t_client_data *client_data)
{
    json_t *json = json_object();
    json_t *chat = json_object();

    json_object_set_new(json, "type", json_string("open_chat"));

    json_object_set_new(chat, "chat_id", json_string(g_object_get_data(G_OBJECT(chat_id), "chat_id")));
    json_object_set_new(chat, "user_id", json_string(client_data->user_attr.user_id));
    json_object_set_new(json, "chat", chat);

    client_data->server_attr.request = json;
//    json_decref(chat);

    send_request(client_data);
}

static void clear_chat(t_client_data *client_data)
{
    GtkWidget *msg_list = get_widget("cm_lbox");

    GList *list = gtk_container_get_children(GTK_CONTAINER(msg_list));

    for (GList *gtemp = list; gtemp != NULL; gtemp = gtemp->next)
    {
        gtk_container_remove(GTK_CONTAINER(msg_list), GTK_WIDGET(gtemp->data));
    }

}


static void fill_chat(t_client_data *client_data)
{
    GtkWidget *msg_list = get_widget("cm_lbox");
    clear_chat(client_data);
    json_t *chats_array = json_object_get(client_data->server_attr.response, "messages");
    json_t *msg_obj, *last_msg = json_array_get(chats_array, 0);
    json_t *last_author;
    const char *s_last_author = "-1";
    client_data->state_data = strdup(s_last_author);

    for (int i = 0; i < (int)json_array_size(chats_array); i++)
    {
        msg_obj = json_array_get(chats_array, i);

        gtk_list_box_insert(GTK_LIST_BOX(msg_list), create_msg_widget(msg_obj, s_last_author, client_data), -1);

        last_author = json_object_get(msg_obj, "author_name");
        s_last_author = json_string_value(last_author);
//        gtk_widget_show_all(msg_list);
        client_data->state_data = strdup(json_string_value(json_object_get(msg_obj, "msg_id")));
    }

    GtkAdjustment *adjust;
    adjust = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(get_widget("msg_list_scrld")));

//    cmc_log_info("u%i\n", gtk_adjustment_get_upper(adjust));
//    cmc_log_info("l%i\n", gtk_adjustment_get_lower(adjust));
//    cmc_log_info("v%i\n", gtk_adjustment_get_value(adjust));
//
    gtk_adjustment_set_value(adjust, gtk_adjustment_get_upper(adjust) + 1000000);
//
//    cmc_log_info("u%i\n", gtk_adjustment_get_upper(adjust));
//    cmc_log_info("l%i\n", gtk_adjustment_get_lower(adjust));
//    cmc_log_info("v%i\n", gtk_adjustment_get_value(adjust));

    gtk_stack_set_visible_child(GTK_STACK(get_widget("mapp_hp_stack")),
                                get_widget("mapp_chat_mbox"));
    gtk_widget_show_all(msg_list);
}

void select_chat(GtkListBox *box, GtkListBoxRow *chat, t_client_data *client_data)
{

    char *chat_id = g_object_get_data(G_OBJECT(chat), "chat_id");

    if (client_data->state != atoi(chat_id)) {
        client_data->type = OPEN_CHAT;
        prepare_request(chat, client_data);
        fill_chat(client_data);
    }
}