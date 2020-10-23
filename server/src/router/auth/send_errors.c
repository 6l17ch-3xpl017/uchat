#include "server.h"

/*
 * send json status (error or correct work of function)
*/
void send_status(int socketfd, int status, char *func) {
    json_t *json = json_object();
    json_object_set_new(json, "type", json_string(func));
    json_object_set_new(json, "status", json_integer(status));
    char *result = json_dumps(json, 0);
    write(socketfd, result, strlen(result));
    json_decref(json);
}
