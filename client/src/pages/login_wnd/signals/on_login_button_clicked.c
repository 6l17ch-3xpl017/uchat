#include "client.h"

void on_login_button_clicked(GtkButton *login_btn, t_client_data *client_data)
{
    client_data->type = LOGIN;

    if ((errno = create_user_data(client_data)) == 104 || errno == 103 || errno == 0)
    {
        gtk_widget_show_now(get_widget("chat_app"));
        gtk_widget_hide(get_widget("login_window"));
        gtk_widget_hide(get_widget("reg_window"));
    }
    else
    {
        //ToDo: Raise error in window
        cmc_log_error("error: %d", errno);
    }
}
