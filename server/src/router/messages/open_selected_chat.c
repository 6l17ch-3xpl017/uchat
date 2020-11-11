#include "server.h"

void open_selected_chat(json_t *income_json, t_thread_sockuser *socket) {
    json_t *user_message;
    t_chat *Chat = malloc(sizeof(t_chat));

    user_message = json_object_get(income_json, "");
    get_all_messages_from_db(Chat);
}
