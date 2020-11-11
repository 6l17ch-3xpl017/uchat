#include "client.h"

void login_wnd_destroy(GtkWindow *login_wnd, t_client_data *client_data)
{
    gtk_window_set_destroy_with_parent(login_wnd, TRUE);

    // ToDo: free client_data;
    // g_object_unref(builder);

    gtk_main_quit();

    // ToDo: check leaks

    exit(0);
}