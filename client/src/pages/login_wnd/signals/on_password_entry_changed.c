#include "client.h"

void on_password_entry_changed(GtkEntry *p_entry, t_client_data *client_data)
{
    strcpy(client_data->user_attr.password, gtk_entry_get_text(p_entry));
}