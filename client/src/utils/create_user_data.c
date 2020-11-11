#include "client.h"

int create_user_data(t_client_data *client_data)
{
    client_data->server_attr.request = json_object();

    json_t *user = json_object();
    json_object_set_new(user, "nickname", json_string(client_data->user_attr.username));
    json_object_set_new(user, "password", json_string(client_data->user_attr.password));

    if (strcmp(client_data->type, REGISTER) == 0)
    {
        json_object_set_new(user, "email", json_string(
                gtk_entry_get_text(GTK_ENTRY(get_widget("reg_email_entry")))));
        json_object_set_new(user, "age", json_string(
                gtk_entry_get_text(GTK_ENTRY(get_widget("reg_age_entry")))));
        json_object_set_new(user, "fullname", json_string(
                gtk_entry_get_text(GTK_ENTRY(get_widget("reg_fullname_entry")))));
        json_object_set_new(user, "ph_number", json_string(
                gtk_entry_get_text(GTK_ENTRY(get_widget("reg_phonenumber_entry")))));
        json_object_set_new(user, "user_photo", json_string(client_data->user_attr.user_photo));
        json_object_set_new(user, "options", json_string(client_data->user_attr.options));
    }

    json_object_set_new(client_data->server_attr.request, "type", json_string(client_data->type));
    json_object_set_new(client_data->server_attr.request, "user", user);
//    json_decref(user);

    return send_json(client_data);
}