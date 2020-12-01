#include "server.h"

static char *pack_json_updated_msg(t_message *Message) {
    json_t *msg_array, *msg, *json;
    json = json_object();
    msg = json_object();
    msg_array = json_array();
    /* send all newly appeared messages in chat */
    for (t_message *head = Message; head; head = head->next) {
        json_object_set_new(msg, "author", json_string(head->message_owner_id));
        json_object_set_new(msg, "author_name", json_string(head->message_owner_name));
        json_object_set_new(msg, "chat_id", json_string(head->chat_id));
        json_object_set_new(msg, "msg_content", json_string(head->message_content));
        json_object_set_new(msg, "msg_type", json_string(head->type));
        json_object_set_new(msg, "msg_id", json_string(head->message_id));
        json_object_set_new(msg, "time", json_string(head->time));
        json_object_set_new(msg, "modified", json_integer(head->changed));
        json_object_set_new(msg, "deleted", json_integer(head->deleted));
        json_array_append_new(msg_array, msg);
        msg = json_object();
    }
    json_object_set_new(json, "type", json_string("ping"));
    json_object_set_new(json, "status", json_integer(UPDATED));
    json_object_set_new(json, "messages", msg_array);
    return json_dumps(json, 0);
}

void check_for_updates(json_t *income_json, struct ns_connection *socket) {
    char *msg_id = NULL, *chat_id = NULL, *json_string = NULL;
    t_message *msg = NULL;

    chat_id = mx_itoa((int)json_integer_value(json_object_get(income_json, "mode")));
    json_unpack(income_json, "{s:s}, {s:i}", "msg_id", &msg_id, "mode", &chat_id);
    msg = messages_from_id(msg_id, chat_id);
    if (msg != NULL && msg_id[0] != '0') {
        json_string = pack_json_updated_msg(msg);
        puts(json_string); //print json
        ns_send(socket, json_string, (int) strlen(json_string));
    }
    else
    {
        json_t *json = json_object();
        json_object_set(json, "status", json_integer(NO_UPDATES));
        json_string = json_dumps(json, 0);
        ns_send(socket, json_string, (int) strlen(json_string));
    }
}

