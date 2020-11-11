#include "client.h"

void on_username_entry_changed(GtkEntry *u_entry, t_client_data *client_data)
{
    strcpy(client_data->user_attr.username, gtk_entry_get_text(u_entry));

    if (gtk_widget_get_visible(get_widget("reg_window")))
    {
        gtk_label_set_text(GTK_LABEL(get_widget("reg_new_username")), client_data->user_attr.username);
    }
}