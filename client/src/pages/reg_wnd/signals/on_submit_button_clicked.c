#include "client.h"

void on_submit_button_clicked(GtkButton *reg_submit_button, t_client_data *client_data)
{
    client_data->type = REGISTER;

    if ((errno = create_user_data(client_data)) == 107)
    {
        gtk_widget_show_now(get_widget("chat_app"));
//        gtk_widget_hide(get_widget("login_window"));
        gtk_widget_hide(get_widget("reg_window"));
    }
    else
    {
        //ToDo: Raise error in window
        cmc_log_error("error: %d", errno);
    }
}