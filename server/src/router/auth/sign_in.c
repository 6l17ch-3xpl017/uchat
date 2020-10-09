#include "server.h"

static void user_struct_filling_with_null(t_user *User) {
    User->id = NULL;
    User->nickname = NULL;
    User->password = NULL;
    User->email = NULL;
    User->age = NULL;
    User->fullname = NULL;
    User->ph_number = NULL;
    User->user_photo = NULL;
    User->option = NULL;
}

static void json_sign_in_parse(t_user *User, json_t *user_in) {
    json_t *user_out, *nickname, *email, *password;

    nickname = json_object_get(user_in, "nickname");
    email = json_object_get(user_in, "email");
    password = json_object_get(user_in, "password");
    if (strcmp(json_string_value(nickname), "") != 0) {
        User->nickname = strdup(json_string_value(nickname));
    } else {
        User->email = strdup(json_string_value(email));
    }
    User->password = strdup(json_string_value(password));
    json_decref(nickname);
    json_decref(email);
    json_decref(password);
}

bool user_sign_in(json_t *income_json, t_thread_sockuser *socket) {
    t_user *User;
    json_t *user_in, *user_out, *chat_array;

    init_database();
    User = (t_user *) malloc(sizeof(t_user));
    user_in = json_object_get(income_json, "user");
    if (!json_is_object(user_in)) {
        // init and send json error status
        send_json_to_socket(socket->socket, unknown_error, "sign_in");
        return 0; // false
    } else {
        // move user`s input data to structure
        user_struct_filling_with_null(User);
        // extract input data from user
        json_sign_in_parse(User, user_in);
        // check whether client is registered
//        if (user_in_db(User) == -4) { //todo add enum in db inc for errors
//            send_json_to_socket(socket->socket, not_reg_user, "sign_in");
//        } else {
//            // init and send json OK status to client
//            send_json_to_socket(socket->socket, ok, "sign_in");
//            user_out = json_object();
//            json_object_set_new(user_out, "user", json_string("//////////////////"));
//            chat_array = json_array();
//            //todo for_loop to check how much chats has user!!!!!!!!!!!!!!!!
//            for (int i = 0; i < 20; i++) {
//                json_object_set_new(user_out, "chat", json_string("/////////////"));
//                json_array_set_new(chat_array, i, user_out);
//            }
//        }
    }
    //-------------------------------------------------
    printf("%d", user_in_db(User));
    printf("\nNICK: %s\n", User->nickname);
    printf("PASS: %s\n", User->password);
    printf("USER_IN_DB (sign_in func)\n");
    //-------------------------------------------------

    return 1; // true
}
