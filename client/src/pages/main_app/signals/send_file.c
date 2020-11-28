#include "client.h"

static json_t *create_msg(int msg_type, char *author, char *content)
{
    json_t *msg = json_object();
    char *str_time = mx_strnew(256);
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);

    strftime(str_time, 256, "%r", ptm);
    json_object_set(msg, "author_name", json_string(author));
    json_object_set(msg, "msg_content", json_string(content));
    json_object_set(msg, "time", json_string(str_time));
    json_object_set(msg, "msg_type", json_string("img"));

    mx_strdel(&str_time);
    return msg;
}

void choose_file(GtkFileChooser *chooser, t_client_data *client_data)
{
    GFile *f = gtk_file_chooser_get_file(chooser);
    GBytes *bytes = g_file_load_bytes(f, NULL, NULL, NULL);
    gsize size;
    guchar *img = (guchar *)g_bytes_get_data(bytes, &size);
    gchar *img64 = g_base64_encode(img, size);
    GtkWidget *listbox = get_widget("cm_lbox");

//    GtkWidget *msg = gtk_image_new_from_file(gtk_file_chooser_get_filename(chooser));

    GtkWidget *msg = create_msg_widget(create_msg(POLL_MSG, client_data->user_attr.username, img64),
                                       client_data->gtk_attr.last_msg_author, client_data);

    gtk_list_box_insert(GTK_LIST_BOX(listbox), msg, -1);
    gtk_widget_show_all(listbox);

    gtk_widget_hide(get_widget("file_chooser_popup"));



    client_data->type = SEND_MSG;
    char *msg_type = strdup("img");
    create_msg_json(img64, msg_type, client_data);
    client_data->state_data = mx_itoa(atoi(client_data->state_data) + 1);
}

void send_file(GtkButton *btn, t_client_data *client_data)
{
    gtk_widget_show_now(get_widget("file_chooser_popup"));
}
