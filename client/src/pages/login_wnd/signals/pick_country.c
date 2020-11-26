#include "client.h"

gboolean update_gui(t_client_data *client_data)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("temp.png", 32, 24, TRUE, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(get_widget("country_flag")), pixbuf);
    return FALSE;
}


void pick_country(GtkComboBox *countries, t_client_data *client_data)
{
    char *country = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(countries));
    get_country(client_data, country);
    update_gui(client_data);
    mx_strdel(&country);
}
