#include "server.h"

static t_message *json_new_chat_parse(json_t *income_json) {
    t_message *Message = NULL;
    json_t *user_message;
    Message = (t_message *)malloc(sizeof(t_message));

    user_message = json_object_get(income_json, "message");
    Message->chat_id = strdup(json_string_value(json_object_get(user_message, "chat_id")));
    Message->message_id = NULL;
    Message->message_owner_id = strdup(json_string_value(json_object_get(user_message, "message_owner_id")));
    Message->message_content = strdup(json_string_value(json_object_get(user_message, "message_content")));
    Message->type = NULL; //strdup(json_string_value(json_object_get(user_message, "type")));
    Message->time = 0; // json_integer_value(json_object_get(user_message, "time"));
    Message->option = NULL;
    Message->changed = 0;
    Message->deleted = 0;
    Message->next = NULL;
    json_decref(user_message);
    return Message;
}

void create_new_message(json_t *income_json, t_thread_sockuser *socket) {
    t_message *msg = NULL;
    char *result;
    int check_status = 0;

    msg = json_new_chat_parse(income_json);
    check_status = add_message_to_db(msg);
    result = message_pack_send(msg, check_status);
    write(socket->socket, result, strlen(result));
}
