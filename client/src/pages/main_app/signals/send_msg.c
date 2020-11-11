#include "client.h"

gchar *get_text_from_text_view(GtkTextView *chat_msg_entry)
{
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(chat_msg_entry);

    gtk_text_buffer_get_bounds(buffer, &start, &end);

    return gtk_text_buffer_get_text(buffer, &start, &end, FALSE);;
}

void send_msg(GtkButton *chat_send_btn, t_client_data *client_data)
{
    gchar *text = get_text_from_text_view(GTK_TEXT_VIEW(get_widget("chat_msg_entry")));
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(get_widget("chat_msg_entry")));

    GtkWidget *listbox = get_widget("chat_msg_lst_box");
    GtkWidget *msg = msg_widget_factory(P_MSG, text, client_data->user_attr.username);

    gtk_list_box_insert(GTK_LIST_BOX(listbox), GTK_WIDGET(msg), -1);
    gtk_widget_show_all(listbox);
    gtk_text_buffer_set_text(buffer, "", -1);

    create_msg_json(text, client_data);

    g_free(text);
}
