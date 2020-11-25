#include "server.h"

static void free_chat_struct(t_chat *Chat) {
    if (Chat->chat_id)
        free(Chat->chat_id);
    if (Chat->chat_name)
        free(Chat->chat_name);
    if (Chat->chat_photo)
        free(Chat->chat_photo);
    if (Chat->admin_id)
        free(Chat->admin_id);
    if (Chat->option)
        free(Chat->option);
    free(Chat);
}

void create_new_empty_chat(json_t *income_json, struct ns_connection *socket) {
    json_t *user_list = NULL;

    json_t *users = json_object_get(income_json, "users");
    if (!json_is_array(users)) {
        send_status(NULL, NULL, socket, unknown_error, "new_chat");
        json_decref(users);
        return;
    }
    else {
        char *chat_type;
        t_chat *Chat = Chat = (t_chat *)malloc(sizeof(t_chat));
        init_chat_struct(Chat);
        t_chat *temp_chat;
        temp_chat = Chat;
        chat_type = strdup(json_string_value(json_object_get(income_json, "chat_type")));

        if (strcmp(chat_type, "public") == 0) {
            Chat->chat_name = strdup(json_string_value(json_object_get(income_json, "chat_name")));
            Chat->admin_id = strdup(json_string_value(json_object_get(income_json, "admin_id")));
            Chat->chat_photo = strdup(json_string_value(json_object_get(income_json, "chat_photo")));
        }
        else {
            Chat->admin_id = strdup("1");
            Chat->chat_name = strdup ("23"); // todo add other user nickname
        }
        add_chat_to_db(Chat); // todo check 108
        free_chat_struct(Chat);
        Chat = (t_chat *)malloc(sizeof(t_chat));
        init_chat_struct(Chat);
        for (int i = 0; i < (int)json_array_size(users); i++) {
            Chat->user_in_chat = malloc(sizeof(t_user));
            init_user_struct(Chat->user_in_chat);
            user_list = json_array_get(users, i);
// --------------------------------------------------------------
            char *list = json_dumps(user_list, 0);
            puts(list);
// --------------------------------------------------------------
            Chat->user_in_chat->id = strdup(json_string_value(json_object_get(user_list, "user_id")));
            Chat->next = (t_chat *)malloc(sizeof(t_chat));
            Chat = Chat->next;
            init_chat_struct(Chat);
        }
        /* return pointer to the first node of Chat struct */
        Chat = temp_chat;

        for (int i = 0; i < Chat->number_of_users; i++) {
            add_user_in_chat(Chat->user_in_chat, Chat);
        }
    }
    //todo add user to chat
}

