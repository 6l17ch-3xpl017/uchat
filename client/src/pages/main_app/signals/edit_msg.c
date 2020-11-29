#include "client.h"

//gboolean choose_msg(GtkWidget *widget, GdkEvent *event, t_client_data *client_data)
//{
//    if(event->button.button  == 1)
//    {
//        gtk_widget_show_now(GTK_WIDGET(gtk_builder_get_object(builder, "on_msg_pop")));
//    }
//
//    return TRUE;
//}

void del_row(GtkListBox *box, GtkListBoxRow *row, t_client_data *client_data)
{
    gtk_container_remove(GTK_CONTAINER(box), GTK_WIDGET(row));
}

gboolean edit_msg(GtkWidget *widget, GdkEvent *event, GtkBuilder *builder)
{
    if(event->button.button  == 1)
    {
        gtk_widget_show_now(GTK_WIDGET(gtk_builder_get_object(builder, "on_msg_pop")));
    }

    return TRUE;
}