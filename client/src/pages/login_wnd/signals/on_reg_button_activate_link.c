#include "client.h"

// ToDo: add auto data transfer
void on_reg_button_activate_link(GtkLinkButton *reg_button, t_client_data *client_data)
{
    gtk_widget_show_now(get_widget("reg_window"));
}
