#include "server.h"

static t_user *collect_new_chat_info(json_t *income_json, struct ns_connection *socket, char *user_nick) {
    char *add_user_id = NULL;
    t_user *User = NULL;

    add_user_id = get_id_by_nickname(user_nick);
    User = (t_user *) malloc(sizeof(t_user));
    User->id = strdup(add_user_id);
    User->next = (t_user *) malloc(sizeof(t_user));
    User->next->id = strdup(json_string_value(json_object_get(income_json, "self_name")));
    init_chat_struct(User->chats);
    User->chats->chat_name = strdup(user_nick);
    User->chats->admin_id = strdup(User->next->id);
    //    User->chats->chat_photo = strdup(json_string_value(json_object_get(income_json, "chat_photo")));
    mx_strdel(&user_nick);
    return User;
}


void create_new_empty_chat(json_t *income_json, struct ns_connection *socket) {
    char *result = NULL;
    char *user_nick = NULL;
    int check_status = 0, add_chat_status = 0;

    t_user *User = NULL;
    user_nick = strdup(json_string_value(json_object_get(income_json, "user_name")));
    if (get_id_by_nickname(user_nick) != NULL) {
        User = collect_new_chat_info(income_json, socket, user_nick);
        add_chat_status = add_chat_to_db(User->chats);
        if (add_chat_status == 107) {
            if (add_user_in_chat(User, User->chats) == add_user_in_chat(User->next, User->chats)) {
                check_status = 107;
                result = new_chat_pack_send(User->chats, check_status);
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

