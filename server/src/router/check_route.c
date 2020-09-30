#include "server.h"

void check_route(char *str) {
    json_t *income_json, *type;
    json_error_t error;

    income_json = json_loads(str, 0, &error);
    type = json_object_get(income_json, "type");
    if (strcmp(json_string_value(type), "sign_in") == 0) {
        printf("Ok_in\n");
    } else if (strcmp(json_string_value(type), "sign_up") == 0) {
//        user_sign_up(income_json);
    }
    else if (strcmp(json_string_value(type), "sign_up") == 0) {
        printf("Ok_up\n");
    }
    else {
        printf("error_jopa\n");
    }
}

