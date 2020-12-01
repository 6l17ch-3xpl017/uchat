#include "client.h"

int send_request(t_client_data *client_data)
{
    char *result = json_dumps(client_data->server_attr.request, 0);

    write(client_data->server_attr.socket, result, strlen(result));

//    json_decref(client_data->server_attr.request);
//    mx_strdel(&result);

    return get_response(client_data);
}
