#include "client.h"

static void change_flag(char *link, t_client_data *client_data)
{
    link = strtok(NULL, "|");
    link = strtok(link, "\n");
    t_memory *memory = download_curl(link);

    int fd = open("test.png", O_WRONLY);
    write(fd, memory->memory, memory->size);
    close(fd);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("test.png", 32, 24, TRUE, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(get_widget("country_flag")), pixbuf);

    g_object_unref(pixbuf);
    free(memory->memory);
    free(memory);
}

static bool do_work(t_client_data *client_data)
{
//    usleep(500);
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

    return TRUE;
}

// FixMe: Test Threads
void pick_country(GtkComboBox *countries, t_client_data *client_data)
{
    client_data->gtk_attr.temp_widget = GTK_WIDGET(countries);
//    client_data->thread.pool[0] = calloc(sizeof(struct cmc_thread), 1);
//    cmc_thrd_create(client_data->thread.pool[0], (cmc_thread_proc)do_work, client_data);
    g_thread_new("change_flag", (GThreadFunc)do_work, client_data);

    sleep(3);
//    free(client_data->thread.pool[0]);
//    client_data->gtk_attr.temp_widget = GTK_WIDGET(countries);
//    do_work(client_data);
}
