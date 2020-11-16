#include "client.h"


/**
 * Function create builder from glade file and connects signals with costume user_data
 * @param glade_filename
 * @param client_data
 */

void create_window(const char *glade_filename, t_client_data *client_data)
{
    client_data->gtk_attr.builder = gtk_builder_new();

    if(!glade_filename)
        cmc_log_fatal("Misssing glade file [glade_filename = %s]", glade_filename);

    gtk_builder_add_from_file(client_data->gtk_attr.builder, glade_filename, &client_data->gtk_attr.error);

    g_check_error(client_data->gtk_attr.error, "Builder loaded")

    gtk_builder_connect_signals(client_data->gtk_attr.builder, client_data);
}