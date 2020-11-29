#include "client.h"

void change_img_ava(GtkFileChooser *chooser, t_client_data *client_data)
{
    char *filename = gtk_file_chooser_get_filename(chooser);

    GtkImage *avatar = GTK_IMAGE(get_widget("set_uava"));
    GdkPixbuf *ava_pix = gdk_pixbuf_new_from_file_at_scale(filename, 28, 28, TRUE, NULL);

    gtk_image_set_from_pixbuf(avatar, ava_pix);
    gtk_widget_hide(get_widget("ava_chooser_popup"));
}

void pop_up_uname(GtkWidget *widget, t_client_data *client_data)
{
    cmc_log_info("AAAAAAAAAA");
    gtk_widget_show_now(get_widget("c_uname_pop"));
}

void pop_up_email(GtkWidget *widget, t_client_data *client_data)
{
    gtk_widget_show_now(get_widget("c_email_pop"));
}

void pop_up_number(GtkWidget *widget, t_client_data *client_data)
{
    gtk_widget_show_now(get_widget("c_phone_pop"));
}

void change_avatar(GtkWidget *button, GdkEvent  *event, t_client_data *client_data)
{
    gtk_widget_show_now(get_widget("ava_chooser_popup"));
}

void change_uname(GtkWidget *button, t_client_data *client_data)
{
    GtkLabel *uname = GTK_LABEL(get_widget("set_uname"));
    GtkLabel *guname = GTK_LABEL(get_widget("global_uname"));
    GtkLabel *uname_main = GTK_LABEL(get_widget("hp_udata_uname1"));
    GtkEntry *uentry = GTK_ENTRY(get_widget("c_uname_entry"));
    const char *new_data;

    if ((new_data = gtk_entry_get_text(uentry)))
    {
        gtk_label_set_text(uname, new_data);
        gtk_label_set_text(guname, new_data);
        gtk_label_set_text(uname_main, new_data);
        client_data->user_attr.username = strdup(new_data);
    }
}

void change_email(GtkWidget *button, t_client_data *client_data)
{
    GtkLabel *email = GTK_LABEL(get_widget("set_email"));
    GtkEntry *eentry = GTK_ENTRY(get_widget("c_email_entry"));

    const char *new_data;

    if ((new_data = gtk_entry_get_text(eentry)))
    {
        gtk_label_set_text(email, new_data);
        client_data->user_attr.email = strdup(new_data);
    }
}

void change_phone(GtkWidget *button, t_client_data *client_data)
{
    GtkLabel *number = GTK_LABEL(get_widget("set_number"));
    GtkEntry *pentry = GTK_ENTRY(get_widget("c_phone_entry"));

    const char *new_data;

    if ((new_data = gtk_entry_get_text(pentry)))
    {
        gtk_label_set_text(number, new_data);
        client_data->user_attr.ph_number = strdup(new_data);
    }
}


void show_settings(GtkButton *button, t_client_data *client_data)
{
    GtkLabel *uname = GTK_LABEL(get_widget("set_uname"));
    GtkLabel *guname = GTK_LABEL(get_widget("global_uname"));
    GtkLabel *email = GTK_LABEL(get_widget("set_email"));
    GtkLabel *number = GTK_LABEL(get_widget("set_number"));

    gtk_label_set_text(uname, client_data->user_attr.username);
    gtk_label_set_text(guname, client_data->user_attr.username);

    if (client_data->user_attr.email)
        gtk_label_set_text(email, client_data->user_attr.email);
    else
        gtk_label_set_text(email, "NULL");

    if (client_data->user_attr.ph_number)
        gtk_label_set_text(number, client_data->user_attr.ph_number);
    else
        gtk_label_set_text(number, "NULL");

    gtk_stack_set_visible_child(GTK_STACK(get_widget("mapp_stack")), get_widget("settings_box"));
}
