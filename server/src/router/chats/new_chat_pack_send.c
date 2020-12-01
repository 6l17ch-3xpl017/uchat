#include "server.h"

/**
 * @author Yevheniia Ksonzenko
 * @brief Function to pack and send json string that contains all info on income/outcome message to client
 * @param Message structure contains msg info
 * @param result complete json string
 * @return json string
 */

char *new_chat_pack_send(t_chat *Chat, int status) {
    char *result;
    json_t * json, *users, *users_array;
    json = json_object();
    users = json_object();
    users_array = json_array();

    json_object_set_new(json, "type", json_string("new_chat"));
    json_object_set_new(json, "status", json_integer(status));

    if (status == 107) {
        json_object_set_new(json, "chat_name", json_string(Chat->chat_name));
        json_object_set_new(json, "chat_id", json_string(Chat->chat_id));
        get_users_list_for_chat(Chat);
        for (t_user *head = Chat->user_in_chat; head; head = head->next) {
            json_object_set_new(users, "users_id", json_string(head->id));
            json_object_set_new(users, "users_nickname", json_string(head->nickname));
            json_array_append_new(users_array, users);
            users = json_object();
        }
        json_object_set_new(json, "chat_users", users_array);
    }
    result = json_dumps(json, 0);
    puts("json from server:  ");
    puts(result);
    free_chat_struct(Chat);
    return result;
}
