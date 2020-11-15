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
    User->number_of_chats = 0;
    User->chats = NULL;
}

static void json_sign_in_parse(t_user *User, json_t *user_in) {
    json_t *nickname, *email, *password;

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

/**
 * @author Yevheniia Ksonzenko
 * @brief Function to get all data about user incl chats from database and send to client while authentication
 * @param income_json string with user`s info to check availability in database (nickname/email, password)
 * @param User structure to fill with NULL or user data to send to database
 * @param Chat structure that contains name(s) of chat(s)
 */

t_user *user_sign_in(json_t *income_json, struct ns_connection *socket) {
    t_user *User;
    t_chat *Chat;
    json_t *user_in;
    int check_status;

    puts(json_dumps(income_json, 0));

    User = (t_user *)malloc(sizeof(t_user));
    user_in = json_object_get(income_json, "user");
    if (!json_is_object(user_in)) {
        // init and send json error status
        Chat = NULL;
        send_status(User, Chat, socket, unknown_error, "sign_in");
        return 0; // false
    } else {
        // move user`s input data to structure
        user_struct_filling_with_null(User);
        // extract input data from user
        json_sign_in_parse(User, user_in);
        // check whether user is already registered
        check_status = user_in_db(User);
        if (check_status == 104) {
            get_chats_where_user(User);
        }
        send_status(User, User->chats, socket, check_status, "sign_in");
    }
    //-------------------------------------------------
    printf("%d\n", user_in_db(User)); // print db function result
    //-------------------------------------------------

    return User; // true
}
