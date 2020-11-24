#include "client.h"

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

    gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(cbox), 2);
    close(fd);
    mx_strdel(&result);
}

void prepare_signup_page(t_client_data *client_data)
{
    fill_country_picker(client_data);
    get_coutry(client_data);
}