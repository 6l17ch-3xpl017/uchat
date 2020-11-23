#include "client.h"

static int status_handler(t_client_data *client_data)
{
    if (strcmp(client_data->type, LOGIN) is 0)

        switch (client_data->server_attr.status)
        {
            case 103:
                change_lwnd_mstack(client_data, rstack);
                return 103;

            case 104:
                return 104;

            case 105:
                return 105;

            default:
                cmc_log_fatal("Unknown Error [%i]", client_data->server_attr.status);
        }

    else if (strcmp(client_data->type, REGISTER) is 0)

        switch (client_data->server_attr.status)
        {
            case 107:
                return 107;

            default:
                cmc_log_fatal("Unknown Error [%i]", client_data->server_attr.status);
        }

    else if(strcmp(client_data->type, OPEN_CHAT) is 0)
    {
        switch (client_data->server_attr.status)
        {
            case 1:
                return 1;

            default:
                cmc_log_fatal("Unknown Error [%i]", client_data->server_attr.status);
        }
    }

    cmc_log_fatal("Unknown Type [%s]", client_data->type);
}

int get_response(t_client_data *client_data)
{
    if (client_data->server_attr.response != NULL)
        json_decref(client_data->server_attr.response);

    client_data->server_attr.response = json_loadfd(client_data->server_attr.socket, JSON_DISABLE_EOF_CHECK, NULL);

    /* *************************************************************************************************************** */
    cmc_log_info("%s", json_dumps(client_data->server_attr.response, 0));                                            //*/
    /* *************************************************************************************************************** */

    json_unpack(client_data->server_attr.response, "{s:i, s:s}", "status",
                &client_data->server_attr.status, "user_id",
                &client_data->user_attr.user_id);


    return status_handler(client_data);
}