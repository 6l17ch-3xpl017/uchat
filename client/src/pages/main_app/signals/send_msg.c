#include "client.h"

gchar *get_text_from_text_view(GtkTextView *chat_msg_entry)
{
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(chat_msg_entry);

    gtk_text_buffer_get_bounds(buffer, &start, &end);

    return gtk_text_buffer_get_text(buffer, &start, &end, FALSE);;
}

json_t *create_msg(int msg_type, char *author, char *content)
{
    json_t *msg = json_object();
    char *str_time = mx_strnew(256);
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);

    strftime(str_time, 256, "%r", ptm);
    json_object_set(msg, "author", json_string(author));
    json_object_set(msg, "msg_content", json_string(content));
    json_object_set(msg, "time", json_string(str_time));

    mx_strdel(&str_time);
    return msg;
}

void send_msg(GtkWidget *widget, GdkEventKey *event, t_client_data *client_data)
{
    GtkAdjustment *adjust;

    if (event->keyval == GDK_KEY_Return && !(event->state & GDK_SHIFT_MASK))
    {
        gchar *text = get_text_from_text_view(GTK_TEXT_VIEW(get_widget("chat_msg_entry")));
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(get_widget("chat_msg_entry")));

        GtkWidget *listbox = get_widget("cm_lbox");
//        GtkWidget *msg = msg_widget_factory(P_MSG, text, client_data->user_attr.username);
//        GtkWidget *msg = gtk_label_new(text);
        GtkWidget *msg = create_msg_widget(create_msg(POLL_MSG, client_data->user_attr.username, text),
                                           client_data->user_attr.user_id, client_data);

//        create_msg_widget

//        cmc_log_info("%i", gtk_tree_model_iter_n_children(GTK_TREE_MODEL(listbox), NULL));
//        adjust = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(get_widget("msg_list_scrld")));
//        gtk_adjustment_set_value(adjust, gtk_adjustment_get_upper(adjust));

        gtk_list_box_insert(GTK_LIST_BOX(listbox), GTK_WIDGET(msg), -1);
        gtk_widget_show_all(listbox);
        gtk_text_buffer_set_text(buffer, "", -1);

        client_data->type = SEND_MSG;
        create_msg_json(text, client_data);

        adjust = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(get_widget("msg_list_scrld")));

//        cmc_log_info("u%i\n", gtk_adjustment_get_upper(adjust));
//        cmc_log_info("l%i\n", gtk_adjustment_get_lower(adjust));
//        cmc_log_info("v%i\n", gtk_adjustment_get_value(adjust));

        gtk_adjustment_set_value(adjust, 100000);

//        cmc_log_info("u%i\n", gtk_adjustment_get_upper(adjust));
//        cmc_log_info("l%i\n", gtk_adjustment_get_lower(adjust));
//        cmc_log_info("v%i\n", gtk_adjustment_get_value(adjust));
        cmc_log_info("***%s***", client_data->gtk_attr.last_msg_author);
        g_free(text);
    }
    else if (event->state & GDK_SHIFT_MASK)
    {
        adjust = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(get_widget("msg_entry_scrld")));
        gtk_adjustment_set_value(adjust, gtk_adjustment_get_upper(adjust));
    }
}

void test_test()
{
    cmc_log_info("test_test");
}

void test_test1()
{
    cmc_log_info("test_test1");
}
