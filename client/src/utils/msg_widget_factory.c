#include "client.h"

static GtkWidget *create_parent_msg_widget(char *text_msg, char *username)
{

    time_t t = time(NULL);

    GtkWidget *widget = gtk_event_box_new();

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,   5);
    GtkWidget *side_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *top_box  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,   5);

    GtkWidget *user_avatar = gtk_image_new_from_file("../client/resources/glade/images/user.svg");
    GtkWidget *username_label = gtk_label_new(username);
    GtkWidget *msg_time = gtk_label_new(asctime(localtime(&t)));

    GtkWidget *msg_text = gtk_label_new(text_msg);

    gtk_widget_set_halign(msg_text, GTK_ALIGN_START);
    gtk_label_set_line_wrap(GTK_LABEL(msg_text), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(msg_text), 66);
    gtk_label_set_line_wrap_mode(GTK_LABEL(msg_text), PANGO_WRAP_WORD_CHAR);

    gtk_container_add(GTK_CONTAINER(main_box), user_avatar);
    gtk_container_add(GTK_CONTAINER(top_box), username_label);
    gtk_container_add(GTK_CONTAINER(top_box), msg_time);

    gtk_container_add(GTK_CONTAINER(widget), main_box);
    gtk_container_add(GTK_CONTAINER(main_box), side_box);
    gtk_container_add(GTK_CONTAINER(side_box), top_box);
    gtk_container_add(GTK_CONTAINER(side_box), msg_text);

    return widget;
}

static GtkWidget *create_child_msg_widget()
{
    GtkWidget *widget = gtk_event_box_new();
    return widget;
}

GtkWidget *msg_widget_factory(int msg_type, char *text_msg, char *username)
{

    if (msg_type == P_MSG)
        return create_parent_msg_widget(text_msg, username);

    else if (msg_type == C_MSG)
        create_child_msg_widget();

    cmc_log_fatal("Invalid msg_type [%d]", msg_type);
}
