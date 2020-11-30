#include "client.h"

void friend_page(GtkWidget *btn, t_client_data *client_data)
{
    gtk_stack_set_visible_child(GTK_STACK(get_widget("mapp_hp_stack")), get_widget("mapp_mpage"));
}
