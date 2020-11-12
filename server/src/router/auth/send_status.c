#include "server.h"

static char *chat_array_send(t_user *User, t_chat *Chat, json_t *json) {
    json_t *user_out, *chat_array;
    char *result;
    user_out = json_object();
    chat_array = json_array();
    if (User->number_of_chats != 0) {
        for (int i = 0; i < User->number_of_chats; i++) {
            json_object_set_new(user_out, "chat", json_string(Chat->chat_id));
            json_array_append(chat_array, user_out);
        }
    }
    json_object_set_new(json, "user_chats", chat_array);
    result = json_dumps(json, 0);
    return result;
}

/**
 * @author Yevheniia Ksonzenko
 * @brief function sends json status (error or correct work of function)
 * @param status shows error or success number from enum
 * @param func shows name of function in which actions were executed
 */

void send_status(t_user *User, t_chat *Chat, struct ns_connection *conn, int status, char *func) {
    json_t *json;
    char *result = NULL;

    json = json_object();
    json_object_set_new(json, "type", json_string(func));
    json_object_set_new(json, "status", json_integer(status));
    User != NULL ? json_object_set_new(json, "user_id", json_string(User->id)) : 0;
    /* send array with all chats in case of success function execution */
    if ((status == 104 || status == 107) && (strcmp(func, "sign_up") == 0 || strcmp(func, "sign_in") == 0)) {
        result = chat_array_send(User, Chat, json);
        ns_send(conn, mx_itoa(strlen(result)), strlen(mx_itoa(strlen(result))));
        ns_send(conn, "{", 1);
        ns_send(conn, result, strlen(result));
    }
    /* send message pack in case of success function execution */
    else if (status == 107 && (strcmp(func, "send_message") == 0)) {
        result = json_dumps(json, 0);
        ns_send(conn, mx_itoa(strlen(result)), strlen(mx_itoa(strlen(result))));
        ns_send(conn, "{", 1);
        ns_send(conn, result, strlen(result));
    }
        /* in case of any other errors */
    else {
        result = json_dumps(json, 0);
        ns_send(conn, mx_itoa(strlen(result)), strlen(mx_itoa(strlen(result))));
        ns_send(conn, "{", 1);
        ns_send(conn, result, strlen(result));
    }
    puts(result); // print json
    json_decref(json);
}

