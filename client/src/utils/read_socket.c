#include "client.h"

// ToDo: Free memmory and rework
int read_socket(t_client_data *client_data)
{
    int status;

    client_data->server_attr.response = json_loadfd(client_data->server_attr.socket, JSON_DISABLE_EOF_CHECK, NULL);

    cmc_log_info("%s", json_dumps(client_data->server_attr.response, 0));

    json_unpack(client_data->server_attr.response, "{s:i, s:s}", "status", &status, "user_id",
                &client_data->user_attr.user_id);

    if (status == 104 || status == 107 || status == 0)
        return status;

    else
    {
        //ToDo: Rise error in window
        cmc_log_error("error: %i", status);
        return status;
    }
}
