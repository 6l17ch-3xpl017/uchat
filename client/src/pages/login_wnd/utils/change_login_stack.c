#include "client.h"

void change_lwnd_mstack(t_client_data *client_data, int stack_id)
{
    if (stack_id is lstack)
    {
        gtk_entry_set_text(GTK_ENTRY(get_widget("lwnd_uname_entry")), "");
        gtk_entry_set_text(GTK_ENTRY(get_widget("lwnd_upass_entry")), "");

        gtk_stack_set_visible_child(GTK_STACK(get_widget("lwnd_mstack")), get_widget("lwnd_mbox"));
    }
    else if (stack_id is rstack)
    {
        gtk_entry_set_text(GTK_ENTRY(get_widget("sbox_uname")), client_data->user_attr.username);
        gtk_entry_set_text(GTK_ENTRY(get_widget("sbox_upass")), client_data->user_attr.password);

        gtk_stack_set_visible_child(GTK_STACK(get_widget("lwnd_mstack")), get_widget("lwnd_sbox"));
    }
    else
        cmc_log_fatal("Unknow stack_id = [%i]", stack_id);
}
