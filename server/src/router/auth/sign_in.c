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

bool user_sign_in(json_t *income_json) {
    t_user *User;
    json_t *user, *nickname, *email, *password;

    init_database();
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
    user_struct_filling_with_null(User);
    if (strcmp(json_string_value(nickname), "") != 0) {
        User->nickname = strdup(json_string_value(nickname));
    }
    else {
        User->email = strdup(json_string_value(email));
    }
    User->password = strdup(json_string_value(password));

    //-------------------------------------------------
    printf("%s",user_in_db(User));
    printf("\nNICK: %s\n", User->nickname);
    printf("PASS: %s\n", User->password);
    printf("USER_IN_DB (sign_in func)\n");
    //-------------------------------------------------

    return 1; // true
}
