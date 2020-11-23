#include "client.h"

GtkWidget *create_chat_widget(json_t *chat_object)
{
    GtkBuilder *builder = create_widget_from_template(CHAT_WIDGET_CLASS);
    GtkWidget *widget = GTK_WIDGET(gtk_builder_get_object(builder, "achat_lboxr"));
    GtkLabel *chat_name_lable = GTK_LABEL(gtk_builder_get_object(builder, "chat_name"));
    json_t *name_obj = json_object_get(chat_object, "chat_name");
    json_t *id_obj = json_object_get(chat_object, "chat_id");

    char *chat_id = strdup(json_string_value(id_obj));

    gtk_label_set_text(chat_name_lable, json_string_value(name_obj));
    g_object_set_data(G_OBJECT(widget), "chat_id", (gpointer)chat_id);

    json_decref(chat_object);
    json_decref(name_obj);
    json_decref(id_obj);

//    g_object_unref(builder);

    return widget;
}
