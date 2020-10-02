#include "server.h"

bool user_sign_up(json_t *income_json) {
    json_t *user;

    user = json_object_get(income_json,"user");
    if (!json_is_object(user)) {
        printf("error: user is not an json object");
        return 0;
    }
    t_user *User = NULL;
    User = (t_user*)malloc(sizeof(t_user));
    User->nickname = strdup(json_string_value(json_object_get(user,"nickname")));
    User->password = strdup(json_string_value(json_object_get(user,"password")));
    User->email = strdup(json_string_value(json_object_get(user,"email")));
    User->age = strdup(json_string_value(json_object_get(user,"age")));
    User->fullname = strdup(json_string_value(json_object_get(user,"fullname")));
    User->ph_number = strdup(json_string_value(json_object_get(user,"ph_number")));
    User->user_photo = strdup(json_string_value(json_object_get(user,"user_photo")));
    User->option = strdup(json_string_value(json_object_get(user,"option")));
    json_decref(user);

    return 1;
}

