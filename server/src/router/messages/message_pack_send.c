#include "server.h"

char *message_pack_send(t_chat *Chat, t_message *Message, json_t *json) {
    json_t *users_array, *msg_array, *users, *msg;
    char *result;
    users = json_object();
    msg = json_object();
    users_array = json_array();
    msg_array = json_array();

    json_object_set_new(json, "chat_id", json_string(Message->chat_id));

    for (t_chat *head = Chat; head != NULL; head = head->next) {
        json_object_set_new(users, "users", json_string(Chat->user_in_chat->id));
        json_array_append(users_array, users);
    }
    json_object_set_new(msg, "author", json_string(Message->message_owner_id));
    json_object_set_new(msg, "prev", json_string(Message->prev->message_owner_id));
    json_object_set_new(msg, "content", json_string(Message->message_content));
    json_object_set_new(msg, "type", json_string(Message->type));
    json_object_set_new(msg, "modified", json_integer(Message->changed));
    json_object_set_new(msg, "deleted", json_integer(Message->deleted));
    json_object_set_new(msg, "next", json_string(Message->next->message_owner_id));
    json_array_append(msg_array, msg);

    json_object_set_new(json, "user_chats", users_array);
    json_object_set_new(json, "message", msg_array);
    result = json_dumps(json, 0);
    return result;
}
