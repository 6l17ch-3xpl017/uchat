#include "client.h"

static void get_response_size(t_client_data *client_data)
{
    char temp_buf[2];
    temp_buf[1] = '\0';
    client_data->server_attr.response_size = 0;

    while (read(client_data->server_attr.socket, &temp_buf, 1))
    {
        if (!mx_isdigit(temp_buf[0]))
            break;

        client_data->server_attr.response_size += temp_buf[0] + '0';
    }
}

static void malloc_and_read(t_client_data *client_data)
{
    get_response_size(client_data);
    client_data->server_attr.response = calloc(client_data->server_attr.response_size, sizeof(char));
    read(client_data->server_attr.socket, client_data->server_attr.response, client_data->server_attr.response_size);
}

// ToDo: Free memmory and rework
int read_socket(t_client_data *client_data)
{
//    malloc_and_read(client_data);
//    json_t *response = json_loads(client_data->server_attr.response, 0, NULL);
//    json_t *status_j = json_object_get(response, "status");

//    free(client_data->server_attr.response); //ToDo: Rework that free;

    int status;

    client_data->server_attr.response = json_loadfd(client_data->server_attr.socket, JSON_DISABLE_EOF_CHECK, NULL);

    cmc_log_info("%s", json_dumps(client_data->server_attr.response, 0));

    json_unpack(client_data->server_attr.response, "{s:i}", "status", &status);

    if (status == 104 || status == 107 || status == 0)
        return status;

    else
    {
        //ToDo: Rise error in window
        cmc_log_error("error: %i", status);
        return status;
    }
}
