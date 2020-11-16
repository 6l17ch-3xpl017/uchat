#include "server.h"

static void init_msg_struct(t_message *Message) {
    Message->chat_id = NULL;
    Message->message_content = NULL;
    Message->message_id = NULL;
    Message->next = NULL;
    Message->type = NULL;
    Message->option = NULL;
    Message->message_owner_id = NULL;
    Message->changed = 0;
    Message->deleted = 0;
}

void open_selected_chat(json_t *income_json, struct ns_connection *socket) {
    json_t *user_message, *users_array, *msg_array, *users, *msg, *json;
    int m_status = 0, u_status = 0, check_status = 1;
    char *result, *input_user_id;
    t_chat *Chat = malloc(sizeof(t_chat));

    user_message = json_object_get(income_json, "chat");
    init_chat_struct(Chat);

//
//    if (strcmp(json_string_value(json_object_get(user_message, "chat_type")), "public") == 0) {
//        Chat->chat_name = strdup(json_string_value(json_object_get(user_message, "chat_name")));
//    }

    puts(json_dumps(income_json, 0));


    input_user_id = strdup(json_string_value(json_object_get(user_message, "user_id")));
    Chat->chat_id = strdup(json_string_value(json_object_get(user_message, "chat_id")));
    u_status = get_users_list_for_chat(Chat);
    m_status = get_all_messages_from_db(Chat);

    if (m_status != u_status) {
        check_status = request_failed;
    }

    users = json_object();
    msg = json_object();
    users_array = json_array();
    msg_array = json_array();
    json = json_object();
    /* send array of all chat users except inquiring user */
    for (t_user *head = Chat->user_in_chat; head; head = head->next) {
        json_object_set_new(users, "users_id", json_string(head->id));
        json_object_set_new(users, "username", json_string(head->nickname));
        json_array_append_new(users_array, users);
        users = json_object();
    }
    for (t_message *head = Chat->next_message; head; head = head->next) {
        json_object_set_new(msg, "author", json_string(head->message_owner_id));
//        puts(head->type);
        json_object_set_new(msg, "msg_type", json_string(head->type));
        json_object_set_new(msg, "msg_id", json_string(head->message_id));
        json_object_set_new(msg, "msg_content", json_string(head->message_content));
        json_object_set_new(msg, "time", json_integer(head->time));
        json_object_set_new(msg, "modified", json_integer(head->changed));
        json_object_set_new(msg, "deleted", json_integer(head->deleted));

        json_array_append_new(msg_array, msg);
        msg = json_object();
    }
    json_object_set_new(json, "type", json_string("open_chat"));
    json_object_set_new(json, "status", json_integer(check_status));
    json_object_set_new(json, "chat_id", json_string(Chat->chat_id));
    json_object_set_new(json, "receivers", users_array);
    json_object_set_new(json, "messages", msg_array);
    result = json_dumps(json, 0);
//    ns_send(socket, result, strlen(result));
//    ns_send(socket, "{", 1);
    ns_send(socket, result, strlen(result));
//    mx_printstr("from server (open_selected_chat): ");
    puts(result);
    free(Chat->chat_id);
    if (Chat->chat_name)
        free(Chat->chat_name);
    free(Chat);
}
