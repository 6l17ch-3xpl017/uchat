#include "client.h"

const char *ui = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                 "<!-- Generated with glade 3.22.2 -->\n"
                 "<interface>\n"
                 "  <requires lib=\"gtk+\" version=\"3.20\"/>\n"
                 "  <object class=\"GtkListBoxRow\" id=\"achat_lboxr\">\n"
                 "    <property name=\"visible\">True</property>\n"
                 "    <property name=\"can_focus\">True</property>\n"
                 "    <property name=\"valign\">center</property>\n"
                 "    <child>\n"
                 "      <object class=\"GtkBox\">\n"
                 "        <property name=\"visible\">True</property>\n"
                 "        <property name=\"can_focus\">False</property>\n"
                 "        <property name=\"valign\">center</property>\n"
                 "        <property name=\"margin_top\">5</property>\n"
                 "        <property name=\"margin_bottom\">5</property>\n"
                 "        <child>\n"
                 "          <object class=\"GtkFixed\">\n"
                 "            <property name=\"visible\">True</property>\n"
                 "            <property name=\"can_focus\">False</property>\n"
                 "            <property name=\"halign\">center</property>\n"
                 "            <property name=\"valign\">center</property>\n"
                 "            <child>\n"
                 "              <object class=\"GtkImage\" id=\"avatar_img\">\n"
                 "                <property name=\"visible\">True</property>\n"
                 "                <property name=\"can_focus\">False</property>\n"
                 "                <property name=\"halign\">center</property>\n"
                 "                <property name=\"valign\">center</property>\n"
                 "                <property name=\"pixbuf\">no_avatar_icon.svg</property>\n"
                 "              </object>\n"
                 "            </child>\n"
                 "            <child>\n"
                 "              <object class=\"GtkImage\" id=\"status_img\">\n"
                 "                <property name=\"visible\">True</property>\n"
                 "                <property name=\"can_focus\">False</property>\n"
                 "                <property name=\"halign\">center</property>\n"
                 "                <property name=\"valign\">center</property>\n"
                 "                <property name=\"pixbuf\">green_ico.svg</property>\n"
                 "              </object>\n"
                 "              <packing>\n"
                 "                <property name=\"x\">22</property>\n"
                 "                <property name=\"y\">20</property>\n"
                 "              </packing>\n"
                 "            </child>\n"
                 "          </object>\n"
                 "          <packing>\n"
                 "            <property name=\"expand\">False</property>\n"
                 "            <property name=\"fill\">True</property>\n"
                 "            <property name=\"position\">0</property>\n"
                 "          </packing>\n"
                 "        </child>\n"
                 "        <child>\n"
                 "          <object class=\"GtkLabel\" id=\"chat_name\">\n"
                 "            <property name=\"visible\">True</property>\n"
                 "            <property name=\"can_focus\">False</property>\n"
                 "            <property name=\"valign\">center</property>\n"
                 "            <property name=\"margin_left\">5</property>\n"
                 "            <property name=\"margin_right\">155</property>\n"
                 "            <property name=\"label\" translatable=\"yes\">chat_name</property>\n"
                 "          </object>\n"
                 "          <packing>\n"
                 "            <property name=\"expand\">False</property>\n"
                 "            <property name=\"fill\">True</property>\n"
                 "            <property name=\"position\">1</property>\n"
                 "          </packing>\n"
                 "        </child>\n"
                 "        <child>\n"
                 "          <object class=\"GtkLabel\">\n"
                 "            <property name=\"visible\">True</property>\n"
                 "            <property name=\"can_focus\">False</property>\n"
                 "            <property name=\"valign\">center</property>\n"
                 "            <property name=\"label\" translatable=\"yes\">X</property>\n"
                 "            <style>\n"
                 "              <class name=\"transparent\"/>\n"
                 "            </style>\n"
                 "          </object>\n"
                 "          <packing>\n"
                 "            <property name=\"expand\">False</property>\n"
                 "            <property name=\"fill\">True</property>\n"
                 "            <property name=\"position\">2</property>\n"
                 "          </packing>\n"
                 "        </child>\n"
                 "      </object>\n"
                 "    </child>\n"
                 "  </object>\n"
                 "</interface>";

GtkWidget *create_chat_widget(json_t *chat_object)
{
    GtkBuilder *builder = gtk_builder_new_from_file(CHAT_WIDGET_CLASS);
    GtkWidget *widget = GTK_WIDGET(gtk_builder_get_object(builder, "achat_lboxr"));
    GtkLabel *chat_name_label = GTK_LABEL(gtk_builder_get_object(builder, "chat_name"));
    json_t *name_obj = json_object_get(chat_object, "chat_name");
    json_t *id_obj = json_object_get(chat_object, "chat_id");

    char *chat_id = strdup(json_string_value(id_obj));

    gtk_label_set_text(chat_name_label, json_string_value(name_obj));
    g_object_set_data(G_OBJECT(widget), "chat_id", (gpointer)chat_id);

//    json_decref(chat_object);
//    json_decref(name_obj);
//    json_decref(id_obj);

//    g_object_unref(builder);

    return widget;
}
