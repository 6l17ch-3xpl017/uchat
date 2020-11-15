#include "client.h"

GtkBuilder *create_widget_from_template(const char *glade_filename)
{
    GtkBuilder *builder = gtk_builder_new();

    if(!glade_filename)
        cmc_log_fatal("Misssing glade file [glade_filename = %s]", glade_filename);

    gtk_builder_add_from_file(builder, glade_filename, NULL);

//    gtk_builder_connect_signals(client_data->gtk_attr.builder, client_data);

    return builder;
}