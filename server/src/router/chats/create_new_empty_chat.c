#include "server.h"

static t_chat *collect_new_chat_info(json_t *income_json, char *new_user_id, char *new_user_nick) {
    t_chat *Chat = NULL;
    Chat = (t_chat *) malloc(sizeof(t_chat));
    Chat->user_in_chat = (t_user *) malloc(sizeof(t_user));
    Chat->user_in_chat->id = strdup(new_user_id);
    Chat->user_in_chat->nickname = strdup(new_user_nick);
    Chat->user_in_chat->next = (t_user *) malloc(sizeof(t_user));
    Chat->user_in_chat->next->id = strdup(json_string_value(json_object_get(income_json, "self_id")));
    Chat->user_in_chat->next->nickname = strdup(json_string_value(json_object_get(income_json, "self_name")));
    /* if user tries to add himself to chat */
    if (strcmp(new_user_nick, Chat->user_in_chat->next->nickname) == 0) {
        Chat->chat_name = strdup("my_messages");
        Chat->admin_id = strdup(Chat->user_in_chat->next->id);
        Chat->user_in_chat->next = NULL;
        Chat->next = NULL;
    }
    else {
        Chat->chat_name = malloc(sizeof(char) * (strlen(new_user_nick) + strlen(Chat->user_in_chat->next->nickname) + 2));
        strcpy(Chat->chat_name, new_user_nick);
        strcat(Chat->chat_name, "_");
        strcat(Chat->chat_name, Chat->user_in_chat->next->nickname);
        Chat->admin_id = strdup(Chat->user_in_chat->next->id);
        Chat->user_in_chat->next->next = NULL;
        Chat->next = NULL;
    }
    mx_strdel(&new_user_nick);
    return Chat;
}


void create_new_empty_chat(json_t *income_json, struct ns_connection *socket) {
    char *result = NULL;
    char *new_user_nick = NULL;
    char *new_user_id = NULL;
    int check_status = 0, add_chat_status = 0;

    t_chat *Chat = NULL;
    new_user_nick = strdup(json_string_value(json_object_get(income_json, "user_name")));

    new_user_id = get_id_by_nickname(new_user_nick);
    if (new_user_id != NULL) {
        Chat = collect_new_chat_info(income_json, new_user_id, new_user_nick);
        add_chat_status = add_chat_to_db(Chat);
        if (add_chat_status == 107) {
            if (add_user_in_chat(Chat->user_in_chat, Chat) == 107) {
                result = new_chat_pack_send(Chat, 107);
                ns_send(socket, result, strlen(result));
            } else {
                check_status = 108;
                send_status(NULL, NULL, socket, check_status, "new_chat");
            }
        }
        else
            send_status(NULL, NULL, socket, add_chat_status, "new_chat");
    }
    else
        send_status(NULL, NULL, socket, login_incorrect, "new_chat");
}

