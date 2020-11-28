#include "client.h"

static void fill_friends(t_client_data *client_data)
{

}

static void fill_chats(t_client_data *client_data)
{
    GtkWidget *chats_list = get_widget("hp_chats");
    json_t *chats_array = json_object_get(client_data->server_attr.response, "user_chats");

    for (int i = 0; i < (int)json_array_size(chats_array); i++)
    {
        json_t *chat_obj = json_array_get(chats_array, i);

        gtk_list_box_insert(GTK_LIST_BOX(chats_list), create_chat_widget(chat_obj), -1);
    }
    gtk_widget_show_all(chats_list);
//    json_decref(chats_array);
}

void load_main_app_data(t_client_data *client_data)
{
    gtk_label_set_text(GTK_LABEL(get_widget("hp_udata_uname1")), client_data->user_attr.username);
    fill_chats(client_data);
}