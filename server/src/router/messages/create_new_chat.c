#include "server.h"

static void chat_struct_filling_with_null(t_chat *Chat) {
    Chat = (t_chat *)malloc(sizeof(t_chat));
    Chat->chat_name = NULL;
    Chat->chat_photo = NULL;
    Chat->chat_id = NULL;
    Chat->option = NULL;
    Chat->admin_id = NULL;
}

static void json_new_chat_parse(t_user *User) {

}

int create_new_chat(json_t *income_json, t_thread_sockuser *socket) {
    t_user *User;
    t_chat *Chat = NULL;

    chat_struct_filling_with_null(Chat);

    return 0;
}
