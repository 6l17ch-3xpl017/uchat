#include "server.h"

int check_route(char *str, t_thread_sockuser *socket) {
    json_t *income_json, *type;
    json_error_t error;
    // create new node
    struct t_thread_sockuser *prev, *head;

    int errorr = 0;
    socklen_t len = sizeof (error);
    int retval = getsockopt (socket->socket, SOL_SOCKET, SO_ERROR, &errorr, &len);


    if (retval != 0) {
        /* there was a problem getting the error code */
        fprintf(stderr, "error getting socket error code: %s\n", strerror(retval));
        return unknown_error;
    }

    if (errorr != 0) {
        /* socket has a non zero error status */
        fprintf(stderr, "socket error: %s\n", strerror(errorr));
    }

    income_json = json_loads(str, 0, &error);
    type = json_object_get(income_json, "type");

    if (strcmp(json_string_value(type), "sign_in") == 0) {
        user_sign_in(income_json, socket);
    }
    else if (strcmp(json_string_value(type), "sign_up") == 0) {
        user_sign_up(income_json, socket);
    }
    // todo create new chat
    else if (strcmp(json_string_value(type), "new_chat") == 0) {
//        create_new_chat(income_json, socket);
    }
    // todo get messages
    else if (strcmp(json_string_value(type), "get_message") == 0) {
        
    }
    // todo if client logged out/disconnected
    else if (strcmp(json_string_value(type), "log_out") == 0) {
        
    }
    else {
        return unknown_error;
    }
//    json_decref(income_json);
    return ok_check_route;
}
