#include "server.h"

static void json_new_chat_parse(t_message *Message, json_t *income_json, t_user **User) {
    json_t *user_message;
    Message = (t_message *)malloc(sizeof(t_message));

    user_message = json_object_get(income_json, "chat_type");
    Message->chat_id = strdup(json_string_value(json_object_get(user_message, "chat_id")));
    if (strcmp(json_string_value(user_message), "public") == 0)  {
        (*User)->chats->chat_name = strdup(json_string_value(json_object_get(user_message, "chat_name")));
        (*User)->chats->admin_id = strdup(json_string_value(json_object_get(user_message, "admin_id")));
    }
    Message->message_id = strdup(json_string_value(json_object_get(user_message, "message_id")));
    Message->message_owner_id = strdup(json_string_value(json_object_get(user_message, "message_owner_id")));
    Message->message_content = strdup(json_string_value(json_object_get(user_message, "message_content")));
    Message->time = json_integer_value(json_object_get(user_message, "time"));
    Message->option = NULL;
    Message->changed = 0;
    Message->deleted = 0;
    Message->next = NULL;
    json_decref(user_message);
}

int create_new_message(json_t *income_json, t_thread_sockuser *socket, t_user *User) {
    t_message *Message = NULL;
    int check_status;

    json_new_chat_parse(Message, income_json, &User);
    check_status = add_message_to_db(Message);
    // TODO func to send message directly to all chat users

    send_status(User, User->chats, socket->socket, check_status, "send_message");
    return 0;
}
