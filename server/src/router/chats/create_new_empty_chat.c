#include "server.h"

static t_chat *collect_new_chat_info(json_t *users) {
    t_chat *temp_chat;
    json_t *user_list = NULL;
    t_chat *Chat = (t_chat *)malloc(sizeof(t_chat));
    init_chat_struct(Chat);
    temp_chat = Chat;
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
    json_decref(user_list);
    json_decref(users);
    /* return pointer to the first node of Chat struct */
    Chat = temp_chat;
    return Chat;
}

void create_new_empty_chat(json_t *income_json, struct ns_connection *socket) {
    char *result = NULL;
    int check_status = 0, chat_status = 0, users_status = 0;

    json_t *users = json_object_get(income_json, "users");
    if (!json_is_array(users)) {
        send_status(NULL, NULL, socket, unknown_error, "new_chat");
        json_decref(users);
        return;
    }
    else {
        t_chat *Chat = Chat = (t_chat *)malloc(sizeof(t_chat));
        init_chat_struct(Chat);
        Chat->chat_type = strdup(json_string_value(json_object_get(income_json, "chat_type")));

        if (strcmp(Chat->chat_type, "public") == 0) {
            Chat->chat_name = strdup(json_string_value(json_object_get(income_json, "chat_name")));
            Chat->admin_id = strdup(json_string_value(json_object_get(income_json, "admin_id")));
            Chat->chat_photo = strdup(json_string_value(json_object_get(income_json, "chat_photo")));
        }
        else {
            Chat->admin_id = strdup("1"); // todo add user`s id who`s sent a request
            Chat->chat_name = strdup ("NEW"); // todo add other user nickname
        }
        chat_status = add_chat_to_db(Chat);
//        free_chat_struct(Chat);
        Chat = collect_new_chat_info(users);

        for (int i = 0; i < Chat->number_of_users; i++) {
            users_status = add_user_in_chat(Chat->user_in_chat, Chat);
        }
        if (chat_status == users_status)
            check_status = successfully_added_to_db;
        else
            check_status = can_not_add_to_database;
        result = new_chat_pack_send(Chat, check_status);
        ns_send(socket, result, strlen(result));
    }
}
