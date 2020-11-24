#include "client.h"

void goto_lwnd_mbox(GtkButton *btn, t_client_data *client_data)
{
    change_lwnd_mstack(client_data, lstack);
}
