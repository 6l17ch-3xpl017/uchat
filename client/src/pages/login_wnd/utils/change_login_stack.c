#include "client.h"

static void set_flag(t_client_data *client_data, char *flag)
{
    t_memory *memory = download_curl(flag);

    int fd = open("test.png", O_WRONLY);
    write(fd, memory->memory, memory->size);
    close(fd);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("test.png", 32, 24, TRUE, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(get_widget("country_flag")), pixbuf);

    g_object_unref(pixbuf);
    free(memory->memory);
    free(memory);
}

static int find_country_id(char *country)
{
    FILE *f = fopen("../client/resources/countries", "r");
    char *result = calloc(sizeof(char), 50);

    for (int i = 0; i < 241; i++)
    {
        fgets(result, 50, f);

        if(strstr(result, country))
        {
            mx_strdel(&result);
            return i;
        }

        bzero(result, 50);
    }

    return 0;
}

static void get_coutry(t_client_data *client_data)
{
    t_memory *memory = download_curl("https://api.ipgeolocation.io/ipgeo?apiKey=169c568962874667a529bf14aa5746ff");

    json_error_t *error = NULL;
    char *country, *flag;

    client_data->user_attr.geo_info = json_loads((char *)memory->memory, 0, error);

    if (error)
        cmc_log_info("%s", error->text);

    json_unpack(client_data->user_attr.geo_info, "{s:s, s:s}", "country_name", &country, "country_flag", &flag);

    gtk_combo_box_set_active(GTK_COMBO_BOX(get_widget("country_pick")), find_country_id(country));

    free(memory->memory);
    free(memory);
}

static void fill_country_picker(t_client_data *client_data)
{
    char *result = calloc(sizeof(char), 100);
    char buf[2];
    buf[1] = '\0';

    int fd = open("../client/resources/new_countries.txt", O_RDONLY);
    GtkComboBoxText *cbox = GTK_COMBO_BOX_TEXT(get_widget("country_pick"));

    while (read(fd, &buf, 1))
    {
        if (buf[0] is '|')
        {
            gtk_combo_box_text_append(cbox, NULL, result);
            bzero(result, 100);

            while (read(fd, &buf, 1))
            {
                if (buf[0] is '\n')
                    break;
            }

            continue;
        }
        strcat(result, buf);
    }

//    gtk_combo_box_set_active(GTK_COMBO_BOX(cbox), 0);
    gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(cbox), 2);
    close(fd);
    mx_strdel(&result);
}

void change_login_stack(t_client_data *client_data)
{
    gtk_stack_set_visible_child(GTK_STACK(get_widget("lwnd_mstack")), get_widget("lwnd_sbox"));

    gtk_entry_set_text(GTK_ENTRY(get_widget("sbox_uname")), client_data->user_attr.username);
    gtk_entry_set_text(GTK_ENTRY(get_widget("sbox_upass")), client_data->user_attr.password);

    fill_country_picker(client_data);
    get_coutry(client_data);

    gtk_widget_show_all(get_widget("lwnd_mstack"));
    gtk_widget_show_all(get_widget("test_box_img"));
}