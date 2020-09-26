#include "../../include/server.h"

bool user_sign_in(json_t *income_json) {
    t_user *User;
    json_t *user, *nickname, *email, *password;

    User = (t_user *)malloc(sizeof(t_user));
    user = json_object_get(income_json, "user");
    if (!json_is_object(user)) {
        printf("error: user is not an json object\n");
        return 0; // false
    }
    // extract input data from user
    nickname = json_object_get(user, "nickname");
    email = json_object_get(user, "email");
    password = json_object_get(user, "password");

    // move user`s input data to structure
    if (strcmp(json_string_value(nickname), "") != 0) {
        User->nickname = strdup(json_string_value(nickname));
    }
    else {
        User->email = strdup(json_string_value(email));
    }
    User->password = strdup(json_string_value(password));
    //TODO send t_user to BD
    return 1; // true
}
