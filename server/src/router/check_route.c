#include "server.h"

int check_route(char *str, t_thread_sockuser *socket) {
    json_t *income_json, *type;
    json_error_t error;
    // create new node
    struct t_thread_sockuser *prev, *head;

    income_json = json_loads(str, 0, &error);
    type = json_object_get(income_json, "type");
    if (strcmp(json_string_value(type), "sign_in") == 0) {
        user_sign_in(income_json, socket);
    }
    else if (strcmp(json_string_value(type), "sign_up") == 0) {
        user_sign_up(income_json, socket);
    }
    else {
        return unknown_error;
    }
    json_decref(income_json);
    return ok_check_route;
}

