#include "server.h"

int create_new_empty_chat(json_t *income_json, t_thread_sockuser *socket) {
    t_chat *Chat = malloc(sizeof(t_chat));
    json_t *chat, *data;
    char *chat_type;
    int array_len;

    chat_type = strdup(json_string_value(json_object_get(income_json, "chat_type")));
    for (size_t i = 0; i < json_array_size(json_object_get(income_json, "users_in_chat")); i++) {
        data = json_array_get(json_object_get(income_json, "users_in_chat"), i);
    }
    if (!json_is_object(data)) {
        Chat->user_in_chat->nickname = NULL;
        send_status(Chat->user_in_chat, Chat, socket->socket, unknown_error, "sign_up");
        json_decref(income_json);
        return 0;
    }

    if (strcmp(chat_type, "public") == 0) {
        Chat->chat_name = strdup(json_string_value(json_object_get(income_json, "chat_name")));
        Chat->admin_id = strdup(json_string_value(json_object_get(income_json, "admin_id")));
    }
    //todo add user to chat
    return 0;
}
