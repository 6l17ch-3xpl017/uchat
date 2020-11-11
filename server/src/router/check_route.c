#include "server.h"

int check_route(char *str, struct ns_connection *socket) {
    json_t *income_json, *type;
    json_error_t error;
    t_user *r_user = NULL;

    income_json = json_loads(str, 0, &error);

    type = json_object_get(income_json, "type");

    if (strcmp(json_string_value(type), "sign_in") == 0)
        r_user = user_sign_in(income_json, socket);

    else if (strcmp(json_string_value(type), "sign_up") == 0) {
        r_user = user_sign_up(income_json, socket);
    }
//    // todo create new chat
    else if (strcmp(json_string_value(type), "new_chat") == 0) {
        create_new_empty_chat(income_json, socket);
    }
    // todo get messages
    else if (strcmp(json_string_value(type), "send_message") == 0) {
        create_new_message(income_json, socket, r_user); // send message to our test_group_chat
    }
    // todo if client logged out/disconnected
    else if (strcmp(json_string_value(type), "log_out") == 0) {
        
    }
    else {
        return unknown_error;
    }
//    puts(r_user->nickname);
//    json_decref(income_json);
    return ok_check_route;
}
