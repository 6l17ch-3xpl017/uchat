//#include "client.h"
//#include "wrapper_libuv.h"
////ToDo: Save some user data in local memory
//
//static int create_user_data()
//{
//    GET_USER_DATA
//    json_t *json = json_object();
//    json_t *user = json_object();
//    char *request = NULL;
//
//    json_object_set_new(user, "nickname", json_string(user_data->user_attr.username));
//    json_object_set_new(user, "password", json_string(user_data->user_attr.password));
//
//    if (strcmp(user_data->struct_attr.type, REGISTER) == 0)
//    {
//        json_object_set_new(user, "email", json_string(user_data->user_attr.email));
//        json_object_set_new(user, "age", json_string(user_data->user_attr.age));
//        json_object_set_new(user, "fullname", json_string(user_data->user_attr.fullname));
//        json_object_set_new(user, "ph_number", json_string(user_data->user_attr.ph_number));
//        json_object_set_new(user, "user_photo", json_string(user_data->user_attr.user_photo));
//        json_object_set_new(user, "options", json_string(user_data->user_attr.options));
//    }
//
//    json_object_set_new(json, "type", json_string(user_data->struct_attr.type));
//    json_object_set_new(json, "user", user);
//
//    request = json_dumps(json, 0);
//
//    write_to_server(user_data->server_attr.connection->handle, json_dumps(json, 0), (int)strlen(request));
//    uv_read_start(user_data->server_attr.connection->handle, alloc_cb, on_read);
//
//    return json_integer_value(
//            json_object_get(
//                    json_loads(user_data->struct_attr.response, 0, NULL), "status"));
//}
//
//void on_lwnd_uname_entry_changed(GtkEditable *lwnd_uname_entry)
//{
//    GET_USER_DATA
//    free(user_data->user_attr.username);
//    user_data->user_attr.username = g_strjoin("", gtk_entry_get_text(GTK_ENTRY(lwnd_uname_entry)), NULL);
//}
//
//void on_lwnd_pass_entry_changed(GtkEditable *lwnd_pass_entry)
//{
//    GET_USER_DATA
//    free(user_data->user_attr.password);
//    user_data->user_attr.password = g_strjoin("", gtk_entry_get_text(GTK_ENTRY(lwnd_pass_entry)), NULL);
//}
//
//static void on_lwnd_submit_btn_clicked(GtkButton *lwnd_submit_btn, GtkApplicationWindow *main_app)
//{
//    cmc_log_info("LOGIN BUTTON CLICKED");
//    GET_USER_DATA
//    user_data->struct_attr.type = LOGIN;
//
//    cmc_log_info("username_entry = %s | password_entry = %s",
//                 user_data->user_attr.username,
//                 user_data->user_attr.password);
//
//    if ((errno = create_user_data()) == 104)
//    {
//        gtk_widget_show_now(GTK_WIDGET(main_app));
//        GtkWidget *toplevel = gtk_widget_get_toplevel(GTK_WIDGET(lwnd_submit_btn));
//        cmc_log_info("TEST");
//    }
//    else
//    {
//        //ToDo: Raise error in window
//        cmc_log_error("error: %d", errno);
//    }
//
//}