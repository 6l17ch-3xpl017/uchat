#include "client.h"

int send_json(t_client_data *client_data)
{
    char *result = json_dumps(client_data->server_attr.request, 0);

    write(client_data->server_attr.socket, result, strlen(result));

    json_decref(client_data->server_attr.request);
    free(result);

    return read_socket(client_data);
}

