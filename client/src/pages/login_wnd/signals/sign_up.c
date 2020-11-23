#include "client.h"

static int check_fields(t_client_data *client_data)
{
    if (!get_entry_text("sbox_uname"))
    {
        gtk_widget_show_now(get_widget("sbox_uname_error"));
        return 0;
    }

    if (!get_entry_text("sbox_upass") || !get_entry_text("sbox_cpass"))
    {
        gtk_widget_show_now(get_widget("sbox_pass_error"));
        return 0;
    }

    if (strcmp(get_entry_text("sbox_upass"), get_entry_text("sbox_cpass")) != 0)
    {
        gtk_widget_show_now(get_widget("sbox_pass_error"));
        return 0;
    }

    if (!get_entry_text("sbox_fname"))
    {
        gtk_widget_show_now(get_widget("sbox_fname_error"));
        return 0;
    }

    else if(!get_entry_text("sbox_lname"))
    {
        gtk_widget_show_now(get_widget("sbox_lname_error"));
        return 0;
    }

    if (!get_entry_text("sbox_email"))
    {
        gtk_widget_show_now(get_widget("sbox_email_error"));
        return 0;
    }

    if (!get_entry_text("sbox_phone"))
    {
        gtk_widget_show_now(get_widget("sbox_phone_error"));
        return 0;
    }

    return 1;
}

// ToDo: Add user photo
static int read_all_fields(t_client_data *client_data)
{
    if(!check_fields(client_data))
        return 0;

    client_data->user_attr.username =  strdup(get_entry_text("sbox_uname"));
    client_data->user_attr.password = strdup(get_entry_text("sbox_upass"));
    client_data->user_attr.fullname =  mx_strjoin(get_entry_text("sbox_fname"),
                                                  get_entry_text("sbox_lname"));
    client_data->user_attr.email =  strdup(get_entry_text("sbox_phone"));
    client_data->user_attr.ph_number =  strdup(get_entry_text("sbox_phone"));
    client_data->user_attr.country =  gtk_combo_box_text_get_active_text(
            GTK_COMBO_BOX_TEXT(get_widget("country_pick")));

    return 1;
}

static void server_singup(t_client_data *client_data)
{
    client_data->server_attr.request = json_object();

    json_t *user = json_object();

    json_object_set_new(user, "nickname", json_string(client_data->user_attr.username));
    json_object_set_new(user, "password", json_string(client_data->user_attr.password));
    json_object_set_new(user, "fullname", json_string(client_data->user_attr.fullname));
    json_object_set_new(user, "email", json_string(client_data->user_attr.email));
    json_object_set_new(user, "ph_number", json_string(client_data->user_attr.ph_number));
    json_object_set_new(user, "country", json_string(client_data->user_attr.country));
    json_object_set_new(client_data->server_attr.request, "type", json_string(client_data->type));
    json_object_set_new(client_data->server_attr.request, "user", user);

    send_request(client_data);

    json_decref(user);
}

void sign_up(GtkButton *signup_btn, t_client_data *client_data)
{
    client_data->type = REGISTER;

    if(read_all_fields(client_data))
    {
        server_singup(client_data);

        if (client_data->server_attr.status == 107)
        {
            load_main_app_data(client_data);
            gtk_widget_show_now(get_widget("main_app"));
        }
        else
        {
            cmc_log_fatal("ERROR = %i", client_data->server_attr.status);
        }
    }
}
