#include "client.h"

static GtkWidget *create_parent(json_t *msg_obj)
{
    GtkBuilder *builder = create_widget_from_template(P_MSG_WIDGET_CLASS);
    GtkWidget *widget = GTK_WIDGET(gtk_builder_get_object(builder, "msg_row"));

    json_t *author = json_object_get(msg_obj, "author_name");
    json_t *time = json_object_get(msg_obj, "time");
    json_t *content = json_object_get(msg_obj, "msg_content");
    json_t *type = json_object_get(msg_obj, "msg_type");

    GtkLabel *uname = GTK_LABEL(gtk_builder_get_object(builder, "uname"));
    GtkLabel *mtime = GTK_LABEL(gtk_builder_get_object(builder, "mtime"));


    if(strcmp(json_string_value(type), "text") is 0)
    {
        GtkTextView *mcontent = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "mcontent"));
        GtkTextBuffer *mbuffer = gtk_text_view_get_buffer(mcontent);
        gtk_text_buffer_set_text(mbuffer, json_string_value(content), -1);
        gtk_widget_show(GTK_WIDGET(mcontent));
    }
    else if (strcmp(json_string_value(type), "img") is 0)
    {
        GtkImage *msg_img = GTK_IMAGE(gtk_builder_get_object(builder, "mimg"));
        gsize img_size;
        guchar *img = g_base64_decode(json_string_value(content), &img_size);
        int fd = open("temp.png", O_WRONLY);

        write(fd, img, img_size);

        gtk_image_set_from_file(msg_img, "temp.png");
        gtk_widget_show(GTK_WIDGET(msg_img));
    }
    else
        cmc_log_fatal("Unknown type: [%s]", json_string_value(type));

    gtk_label_set_text(uname, json_string_value(author));
    gtk_label_set_text(mtime, json_string_value(time));

    return widget;
}


static GtkWidget *create_child(json_t *msg_obj)
{
    GtkBuilder *builder = create_widget_from_template(C_MSG_WIDGET_CLASS);
    GtkWidget *widget = GTK_WIDGET(gtk_builder_get_object(builder, "msg_row"));

    json_t *time = json_object_get(msg_obj, "time");
    json_t *content = json_object_get(msg_obj, "msg_content");
    json_t *type = json_object_get(msg_obj, "msg_type");

    GtkLabel *mtime = GTK_LABEL(gtk_builder_get_object(builder, "mtime"));

    if (strcmp(json_string_value(type), "text") is 0)
    {
        GtkTextView *mcontent = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "mcontent"));
        GtkTextBuffer *mbuffer = gtk_text_view_get_buffer(mcontent);

        gtk_label_set_text(mtime, json_string_value(time));

        gtk_text_buffer_set_text(mbuffer, json_string_value(content), -1);
        gtk_widget_show(GTK_WIDGET(mcontent));
    }
    else if (strcmp(json_string_value(type), "img") is 0)
    {
        GtkImage *msg_img = GTK_IMAGE(gtk_builder_get_object(builder, "mimg"));
        gsize img_size;
        guchar *img = g_base64_decode(json_string_value(content), &img_size);
        int fd = open("temp.png", O_WRONLY);

        write(fd, img, img_size);

        gtk_image_set_from_file(msg_img, "temp.png");
        gtk_widget_show(GTK_WIDGET(msg_img));
    }
    else
        cmc_log_fatal("Unknown type: [%s]", json_string_value(type));

    return widget;
}


GtkWidget *create_msg_widget(json_t *msg_obj, const char *last_author, t_client_data *client_data)
{
    json_t *author = json_object_get(msg_obj, "author_name");

    client_data->gtk_attr.last_msg_author = strdup(json_string_value(author));

//    cmc_log_info("%s | %s", json_string_value(author), last_author);
    if (!last_author)
        last_author = strdup("-1");

    if (last_author is NULL or strcmp(json_string_value(author), last_author) not 0 or last_author[0] is '-')
        return create_parent(msg_obj);

    else
        return create_child(msg_obj);
}