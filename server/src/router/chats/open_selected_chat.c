#include "server.h"

char *pack_json(t_chat *Chat, int check_status, json_t *json) {
    json_t *users_array, *msg_array, *users, *msg;
    users = json_object();
    msg = json_object();
    users_array = json_array();
    msg_array = json_array();
    if (Chat->number_of_users != 0) {
        for (t_user *head = Chat->user_in_chat; head; head = head->next) {
            json_object_set_new(users, "users_id", json_string(head->id));
            json_object_set_new(users, "username", json_string(head->nickname));
            json_array_append_new(users_array, users);
            users = json_object();
        }
    }
    if (Chat->number_of_messages != 0) {
        for (t_message *head = Chat->next_message; head; head = head->next) {
            json_object_set_new(msg, "author", json_string(head->message_owner_id));
            json_object_set_new(msg, "author_name", json_string(head->message_owner_name));
            json_object_set_new(msg, "msg_type", json_string(head->type));
            json_object_set_new(msg, "msg_id", json_string(head->message_id));
            json_object_set_new(msg, "msg_content", json_string(head->message_content));
            json_object_set_new(msg, "chat_id", json_string(head->message_content));
            json_object_set_new(msg, "time", json_string(head->time));
            json_object_set_new(msg, "modified", json_integer(head->changed));
            json_object_set_new(msg, "deleted", json_integer(head->deleted));
            json_array_append_new(msg_array, msg);
            msg = json_object();
        }
    }
    json_object_set_new(json, "type", json_string("open_chat"));
    json_object_set_new(json, "status", json_integer(check_status));
    json_object_set_new(json, "chat_id", json_string(Chat->chat_id));
    json_object_set_new(json, "receivers", users_array);
    json_object_set_new(json, "messages", msg_array);
    return json_dumps(json, 0);
}

void open_selected_chat(json_t *income_json, struct ns_connection *socket) {
    json_t *user_message, *json;
    int check_status = 1;
    char *result;
    t_chat *Chat = malloc(sizeof(t_chat));

    user_message = json_object_get(income_json, "chat");
    init_chat_struct(Chat);
    puts(json_dumps(income_json, 0)); // print json

    Chat->chat_id = strdup(json_string_value(json_object_get(user_message, "chat_id")));
    if (get_users_list_for_chat(Chat) != get_all_messages_from_db(Chat))
        check_status = request_failed;

    json = json_object();
    result = pack_json(Chat, check_status, json);
    ns_send(socket, result, (int)strlen(result));

    puts(result); // print json
    free(Chat->chat_id);
    if (Chat->chat_name)
        free(Chat->chat_name);
    free(Chat);
}
