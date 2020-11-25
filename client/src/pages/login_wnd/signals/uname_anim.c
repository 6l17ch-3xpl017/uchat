#include "client.h"

void uname_anim(GtkEntry *uname, t_client_data *client_data)
{
    GtkLabel *ulable = GTK_LABEL(get_widget("sbox_username_label"));
    gtk_label_set_text(ulable, gtk_entry_get_text(uname));
}
