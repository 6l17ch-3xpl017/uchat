#include "server.h"

static t_chat *chat_struct_filling_with_null() {
    t_chat *Chat = malloc(sizeof(t_chat));
    Chat->chat_name = "1";
    Chat->chat_photo = NULL;
    Chat->chat_id = NULL;
    Chat->option = NULL;
    Chat->admin_id = "1";
    return Chat;
}

/* get all data from json and add it to struct */
static t_user *user_data_struct_fill(json_t *user, struct ns_connection *socket) {
    t_user *User = NULL;
    t_chat  *Chat = malloc(sizeof(t_chat));
    int check_status;

    User = (t_user *) malloc(sizeof(t_user));
    User->id = NULL;
    User->nickname = strdup(json_string_value(json_object_get(user, "nickname")));
    User->password = strdup(json_string_value(json_object_get(user, "password")));
    User->email = strdup(json_string_value(json_object_get(user, "email")));
    User->age = strdup(json_string_value(json_object_get(user, "age")));
    User->fullname = strdup(json_string_value(json_object_get(user, "fullname")));
    User->ph_number = strdup(json_string_value(json_object_get(user, "ph_number")));
    User->user_photo = strdup(json_string_value(json_object_get(user, "user_photo")));
    User->option = NULL; //strdup(json_string_value(json_object_get(user, "option")));
    User->number_of_chats = 0;
    User->chats = NULL;
    check_status = add_user_to_db(User);
    if (check_status == 104 || check_status == 107) {
        User->number_of_chats = 1;
        Chat->chat_id = strdup("1");
        add_chat_to_db(chat_struct_filling_with_null());
        add_user_in_chat(User, Chat);
    }
    send_status(User, Chat, socket, check_status, "sign_up");
    json_decref(user);
    return User;
}

/**
 * @author Yevheniia Ksonzenko
 * @brief Function to get all data about user (filled on reg. page) and send to database
 * @param income_json string with user`s info (nickname, fullname, age, email, password, photo, phone_number)
 *        to add it to database
 * @param User structure to fill with NULL and/or user data to send it to database
 * @param Chat structure to init empty chat
 */
t_user *user_sign_up(json_t *income_json, struct ns_connection *socket) {
    t_user *User = NULL;
//    t_chat *Chat = NULL;
    json_t *user;
    /* receive json from client and check its correctness */
    user = json_object_get(income_json,"user");
    if (!json_is_object(user)) {
        /* init and send json error status */
//        User->nickname = NULL;
        send_status(NULL, NULL, socket, unknown_error, "sign_up");
        json_decref(user);
        return 0;
    }
    /* get all data from json and add it to struct / send OK status to client */
    else {
        /* add user data to database (process locked by mutex) */
    // TODO add mutex function
        User = user_data_struct_fill(user, socket);
        return User;
    }
}



