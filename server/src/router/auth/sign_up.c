#include "server.h"

// send json status to client
static void send_json(int socketfd, char *json_str) {
    json_t *json = json_object();
    json_object_set_new(json, "type:", json_string("status"));
    json_object_set_new(json, "status:", json_string(json_str));
    char *result = json_dumps(json, 0);
    write(socketfd, result, strlen(result));
    json_decref(json);
}
// get all data from json and add it to struct / send to database
static void user_data_struct_fill(json_t *user) {
    t_user *User = NULL;
    User = (t_user *) malloc(sizeof(t_user));
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
// add empty chat to database and fill with NULL
static void chat_struct_creation(void) {
    t_chat *Chat = NULL;
    Chat->chat_id = NULL;
    Chat->chat_name = NULL;
    Chat->admin_id = NULL;
    Chat->chat_photo = NULL;
    Chat->option = NULL;
    add_chat_to_db(Chat);
}

bool user_sign_up(json_t *income_json) {
    json_t *user, *chat, *message;
// receive json from client and check its correctness
    user = json_object_get(income_json,"user");
    if (!json_is_object(user)) {
        // init and send json error status
//        send_json(socketfd, "error: user is not a json object"); //TODO add socketfd from struct list
        json_decref(user);
        return 0;
    }
// get all data from json and add it to struct / send OK status to client
    else {
        // init and send json OK status
//        send_json(socketfd, "ok: user json object is correct"); //TODO add socketfd from struct list
    // add user data to database (process locked by mutex)
    // TODO add mutex function
        user_data_struct_fill(user);
        chat_struct_creation();

        json_decref(user);
        return 1;
    }
}

