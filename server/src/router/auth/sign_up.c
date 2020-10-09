#include "server.h"

// get all data from json and add it to struct / send to database
static void user_data_struct_fill(json_t *user) {
    t_user *User = NULL;
    User = (t_user *) malloc(sizeof(t_user));
    User->id = NULL;
    User->nickname = strdup(json_string_value(json_object_get(user, "nickname")));
    User->password = strdup(json_string_value(json_object_get(user, "password")));
    User->email = strdup(json_string_value(json_object_get(user, "email")));
    User->age = strdup(json_string_value(json_object_get(user, "age")));
    User->fullname = strdup(json_string_value(json_object_get(user, "fullname")));
    User->ph_number = strdup(json_string_value(json_object_get(user, "ph_number")));
    User->user_photo = strdup(json_string_value(json_object_get(user, "user_photo")));
    User->option = strdup(json_string_value(json_object_get(user, "option")));

    add_user_to_db(User);
}

bool user_sign_up(json_t *income_json, t_thread_sockuser *socket) {
    json_t *user, *chat, *message;
// receive json from client and check its correctness
    user = json_object_get(income_json,"user");
    if (!json_is_object(user)) {
        // init and send json error status
        send_json_to_socket(socket->socket, unknown_error, "sign_up");
        json_decref(user);
        return 0;
    }
// get all data from json and add it to struct / send OK status to client
    else {
    // add user data to database (process locked by mutex)
    // TODO add mutex function
        user_data_struct_fill(user);
        // init and send json OK status
        send_json_to_socket(socket->socket, ok, "sign_up");
        json_decref(user);
        return 1;
    }
}

