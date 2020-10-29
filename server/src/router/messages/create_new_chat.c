#include "server.h"

static void json_new_chat_parse(t_message *Message, json_t *user_message) {
    Message = (t_message *)malloc(sizeof(t_message));
    Message->chat_id = strdup(json_string_value(json_object_get(user_message, "message_id")));
    Message->message_content = strdup(json_string_value(json_object_get(user_message, "message_content")));
    Message->message_owner_id = strdup(json_string_value(json_object_get(user_message, "message_owner_id")));
    Message->time = json_integer_value(json_object_get(user_message, "message_owner_id"));
    Message->option = NULL;
    Message->changed = 0;
    Message->next = NULL;
    json_decref(user_message);
}

int create_new_chat(json_t *income_json, t_thread_sockuser *socket) {
    t_message *Message = NULL;
    json_t *user_message;
    int check_status;

    user_message = json_object_get(income_json, "message");

    json_new_chat_parse(Message, user_message);
    check_status = add_message_to_db(Message);
    t_user *User = NULL;
    t_chat *Chat = NULL;
    send_status(User, Chat, socket->socket, check_status, "send_message");
    return 0;
}
