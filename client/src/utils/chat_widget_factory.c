#include "client.h"

GtkWidget *chat_widget_factory(const char *chat_name, gpointer *chat_id)
{
    GtkWidget *chat = gtk_label_new(chat_name);
    g_object_set_data(G_OBJECT(chat), "chat_id", chat_id); // ToDo: Test it

    return chat;
}
