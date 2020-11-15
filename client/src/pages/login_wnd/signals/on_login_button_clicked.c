#include "client.h"

static void fill_chats_lst(t_client_data *client_data)
{
    GtkWidget *chats_list = get_widget("chat_room_lst");
    json_t *chats_array = json_object_get(client_data->server_attr.response, "user_chats");
    json_t *chat_name = NULL;
    json_t *chat_id = NULL;

    for (int i = 0; i < json_array_size(chats_array); i++)
    {
        json_t *chat_obj = json_array_get(chats_array, i);
        chat_id = json_object_get(chat_obj, "chat_id");
        chat_name = json_object_get(chat_obj, "chat_name");

//        GtkWidget *test = chat_widget_factory(json_string_value(chat_name), json_string_value(chat_id));

        gtk_list_box_insert(GTK_LIST_BOX(chats_list), chat_widget_factory(json_string_value(chat_name),
                                                                          (gpointer *) json_string_value(chat_id)), -1);
        gtk_widget_show_all(chats_list);
    }

    // ToDo: Free memmory
}

void on_login_button_clicked(GtkButton *login_btn, t_client_data *client_data)
{
    client_data->type = LOGIN;

    if ((errno = create_user_data(client_data)) == 104 || errno == 103 || errno == 0)
    {
        gtk_widget_show_now(get_widget("chat_app"));
        gtk_widget_hide(get_widget("login_window"));
        gtk_widget_hide(get_widget("reg_window"));

        fill_chats_lst(client_data);
    }
    else
    {
        //ToDo: Raise error in window
        cmc_log_error("error: %d", errno);
    }
}
