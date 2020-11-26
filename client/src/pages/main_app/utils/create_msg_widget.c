#include "client.h"

static GtkWidget *create_parent(json_t *msg_obj)
{
    GtkBuilder *builder = create_widget_from_template(P_MSG_WIDGET_CLASS);
    GtkWidget *widget = GTK_WIDGET(gtk_builder_get_object(builder, "msg_row"));

    json_t *author = json_object_get(msg_obj, "author_name");
    json_t *time = json_object_get(msg_obj, "time");
    json_t *content = json_object_get(msg_obj, "msg_content");

    GtkLabel *uname = GTK_LABEL(gtk_builder_get_object(builder, "uname"));
    GtkLabel *mtime = GTK_LABEL(gtk_builder_get_object(builder, "mtime"));

    GtkTextView *mcontent = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "mcontent"));
    GtkTextBuffer *mbuffer = gtk_text_view_get_buffer(mcontent);

    gtk_label_set_text(uname, json_string_value(author));
    gtk_label_set_text(mtime, json_string_value(time));

    gtk_text_buffer_set_text(mbuffer, json_string_value(content), -1);

//    json_decref(author);
//    json_decref(time);
//    json_decref(content);

    return widget;
}


static GtkWidget *create_child(json_t *msg_obj)
{
    GtkBuilder *builder = create_widget_from_template(C_MSG_WIDGET_CLASS);
    GtkWidget *widget = GTK_WIDGET(gtk_builder_get_object(builder, "msg_row"));

    json_t *time = json_object_get(msg_obj, "time");
    json_t *content = json_object_get(msg_obj, "msg_content");

    GtkLabel *mtime = GTK_LABEL(gtk_builder_get_object(builder, "mtime"));

    GtkTextView *mcontent = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "mcontent"));
    GtkTextBuffer *mbuffer = gtk_text_view_get_buffer(mcontent);

    gtk_label_set_text(mtime, json_string_value(time));

    gtk_text_buffer_set_text(mbuffer, json_string_value(content), -1);

//    json_decref(time);
//    json_decref(content);

    return widget;
}


GtkWidget *create_msg_widget(json_t *msg_obj, const char *last_author, t_client_data *client_data)
{
    json_t *author = json_object_get(msg_obj, "author");

//    if (clinet_data->gtk_attr.last_msg_author)
//        mx_strdel(&clinet_data->gtk_attr.last_msg_author);

    client_data->gtk_attr.last_msg_author = strdup(json_string_value(author));

    cmc_log_info("%s | %s", json_string_value(author), last_author);

    if (strcmp(json_string_value(author), last_author) != 0 || last_author[0] is '-')
        return create_parent(msg_obj);

    else
        return create_child(msg_obj);
}