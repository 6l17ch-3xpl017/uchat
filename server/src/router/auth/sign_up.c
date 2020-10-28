#include "server.h"

static void chat_struct_filling_with_null(t_chat *Chat) {
    Chat = (t_chat *) malloc(sizeof(t_chat));
    Chat->chat_name = NULL;
    Chat->chat_photo = NULL;
    Chat->chat_id = NULL;
    Chat->option = NULL;
    Chat->admin_id = NULL;
}
// get all data from json and add it to struct
static void user_data_struct_fill(json_t *user, t_thread_sockuser *socket, t_chat *Chat) {
    t_user *User = NULL;
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
//    printf("%d\n", check_status);
    chat_struct_filling_with_null(Chat);
//    add_chat_to_db(Chat);
    send_status(User, Chat, socket->socket, check_status, "sign_up");
    json_decref(user);
    printf("CHECK_STATUS_UP: %d\n", check_status);
    printf("AGE: %s\n", User->age);
}

/**
 * @author Yevheniia Ksonzenko
 * @brief Function to get all data about user (filled on reg. page) and send to database
 * @param income_json string with user`s info (nickname, fullname, age, email, password, photo, phone_number)
 * to add it to database
 * @param User structure to fill with NULL and/or user data to send it to database
 * @param Chat structure to init empty chat
 */

bool user_sign_up(json_t *income_json, t_thread_sockuser *socket) {
    t_user *User = NULL;
    t_chat *Chat = NULL;
    json_t *user, *chat, *message;
// receive json from client and check its correctness
    user = json_object_get(income_json,"user");
    if (!json_is_object(user)) {
        // init and send json error status
        // todo User->nickname = NULL ????;
        User->nickname = NULL;
        send_status(User, Chat, socket->socket, unknown_error, "sign_up");
        json_decref(user);
        return 0;
    }
// get all data from json and add it to struct / send OK status to client
    else {
        puts("SIGN_UP_ELSE");
    // add user data to database (process locked by mutex)
    // TODO add mutex function
        user_data_struct_fill(user, socket, Chat);
        return 1;
    }
}



