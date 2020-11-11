#include "server.h"

char *message_pack_send(t_message *Message, int status) {
    json_t *users_array, *msg_array, *users, *msg, *json;
    char *result;
    users = json_object();
    msg = json_object();
    users_array = json_array();
    msg_array = json_array();
    json = json_object();

    json_object_set_new(json, "type", json_string("send_message"));
    json_object_set_new(json, "status", json_integer(status));

    t_chat *current_chat = malloc(sizeof(t_chat));
    init_chat_struct(current_chat);
    current_chat->chat_id = strdup(Message->chat_id);
    get_users_list_for_chat(current_chat);
    json_object_set_new(json, "chat_id", json_string(Message->chat_id));

    for (t_user *head = current_chat->user_in_chat; head; head = head->next) {
        json_object_set_new(users, "users_id", json_string(head->id));
        json_array_append_new(users_array, users);
        users = json_object();
    }
    json_object_set_new(msg, "author", json_string(Message->message_owner_id));
    json_object_set_new(msg, "type", json_string(Message->type));
//    json_object_set_new(msg, "prev", json_string(Message->prev->message_owner_id));
    json_object_set_new(msg, "msg_id", json_string(Message->message_id));
    json_object_set_new(msg, "content", json_string(Message->message_content));
    json_object_set_new(msg, "modified", json_integer(Message->changed));
    json_object_set_new(msg, "deleted", json_integer(Message->deleted));
    json_array_append(msg_array, msg);

    json_object_set_new(json, "receivers", users_array);
    json_object_set_new(json, "message", msg_array);
    result = json_dumps(json, 0);
    puts("json from server:  ");
    puts(result);
    free(current_chat->chat_id);
    free(current_chat);
    return result;
}
