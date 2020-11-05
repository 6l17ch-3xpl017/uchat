#include "server.h"

/**
 * @author Yevheniia Ksonzenko
 * @brief function sends json status (error or correct work of function)
 * @param status shows error or success number from enum
 * @param func shows name of function in which actions were executed
 */

void send_status(t_user *User, t_chat *Chat, int socketfd, int status, char *func) {
    json_t *json, *user_out, *chat_array;
    char *result = NULL;

    json = json_object();
    json_object_set_new(json, "type", json_string(func));
    json_object_set_new(json, "status", json_integer(status));

    /* in case of success function execution */
    if (status == 104 || status == 107) {
        user_out = json_object();
        chat_array = json_array();
        if (User->number_of_chats != 0) {
            for (int i = 0; i < User->number_of_chats; i++) {
                json_object_set_new(user_out, "chat", json_string(Chat->chat_id));
                json_array_append(chat_array, user_out);
            }
        }
//        else if (Chat->number_of_messages != 0 && strcmp(func, "send_message") == 0) {
//        }
//        else if (Chat->number_of_messages != 0 && strcmp(func, "open_chat") == 0) {
//            for (t_message *head = Chat->next_message; head; head == head->next) {
//
//            }
//        }
        json_object_set_new(json, "user_chats", chat_array);
        result = json_dumps(json, 0);
        write(socketfd, result, strlen(result));
    }
    /* in case of any other errors */
    else {
        result = json_dumps(json, 0);
        write(socketfd, result, strlen(result));
    }
    puts(result); // print json
    json_decref(json);
}

