#include "client.h"

static int get_country_cb(void *my_arg, int argc, char **argv, char **columns)
{
    gsize result_size;

    guchar *result = g_base64_decode(argv[1], &result_size);

    int fd = open("temp.png", O_CREAT | O_WRONLY);

    chmod("temp.png", 0777);

    write(fd, result, result_size);
    close(fd);

    return 0;
}

void get_country(t_client_data *client_data, char *country)
{
    char *request = NULL;
    char *err = mx_strnew(100);
    make_sql_request(&request, "SELECT * FROM Countries WHERE country_name = %s;", country);
    sqlite3_exec(client_data->db, request, get_country_cb, request, &err);
    mx_strdel(&request);
}