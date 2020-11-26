#include "client.h"

gboolean update_gui(t_client_data *client_data)
{
    g_mutex_lock(&client_data->thread.mutex_interface);

//    gsize result_size;
//    guchar *img = g_base64_decode("",&result_size);
//    cmc_log_info("%s | %zu", img, result_size);
//
//    int fd = open("test_base.png", O_WRONLY);
//    write(fd, img, result_size);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("temp.png", 32, 24, TRUE, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(get_widget("country_flag")), pixbuf);

    g_mutex_unlock(&client_data->thread.mutex_interface);

    return FALSE;
}

static void change_flag(char *link, t_client_data *client_data)
{
    link = strtok(NULL, "|");
    link = strtok(link, "\n");
    t_memory *memory = download_curl(link);


    int fd = open("temp.png", O_WRONLY | O_CREAT);
    chmod("temp.png", S_IRWXU);

    write(fd, memory->memory, memory->size);
    close(fd);

    update_gui(client_data);

    free(memory->memory);
    free(memory);
}

static bool do_work(t_client_data *client_data)
{
    FILE *f = fopen("../client/resources/new_countries.txt", "r");
    char *result = calloc(sizeof(char), 100);
    char *needle = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(client_data->gtk_attr.temp_widget));

    while (1)
    {
        fgets(result, 100, f);

        if (strstr(result, needle))
        {
            change_flag(strtok(result, "|"), client_data);
            break;
        }
    }

    mx_strdel(&needle);
    mx_strdel(&result);

    return FALSE;
}

void pick_country(GtkComboBox *countries, t_client_data *client_data)
{
    client_data->gtk_attr.temp_widget = GTK_WIDGET(countries);
    g_thread_new("change_flag", (GThreadFunc)do_work, client_data);

    while (gtk_events_pending())
        gtk_main_iteration();
}
