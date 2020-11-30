#include "server.h"

static t_chat *chat_struct_filling_with_null() {
    t_chat *Chat = malloc(sizeof(t_chat));
    Chat->chat_name = "1";
    Chat->chat_photo = NULL;
    Chat->chat_id = NULL;
    Chat->option = NULL;
    Chat->admin_id = "1";
    return Chat;
}


static void ev_handler(struct ns_connection *nc, int ev, void *p) {
    int size = 1048576;
    setsockopt(nc->sock, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

    struct iobuf *io = &nc->recv_iobuf;
    char *income_json = NULL;
    char *buff = mx_strnew(2048);
    if (ev == NS_RECV)
    {
        income_json = strndup(io->buf, io->len);

        check_route(income_json, nc);
        iobuf_remove(io, io->len);
        free(income_json);
    }
    else if (ev == NS_ACCEPT)
    {
        printf("A\n");
    }
    else if (ev == NS_CLOSE)
    {
        puts("X\n");
    }
//    "{"type": "sign_in", "user": {"nickname": "smith", "password": "123321"}}\261\a\002"
//    switch (ev) {
//        case NS_RECV:
//            ns_send(nc, io->buf, io->len);  // Echo message back
//            iobuf_remove(io, io->len);        // Discard message from recv buffer
//            break;
//        default:
//            break;
//    }
}

int main(void) {
    struct ns_mgr mgr;

    ns_mgr_init(&mgr, NULL);
//    iobuf_resize(&mgr.active_connections->recv_iobuf, 1048576);
    init_database();


////    add_chat_to_db(chat_struct_filling_with_null());

    ns_bind(&mgr, "7777", ev_handler, NULL);

    printf("Starting server on port: %s\n", "7777");

    for (;;)
        ns_mgr_poll(&mgr, 1000);

    ns_mgr_free(&mgr);

    return 0;

    //--------------- CHECK PING ---------------

//    char *msg_id =

    //--------------- CREATE NEW CHAT ---------------
//    char *new_chat;
//    json_t *chat = json_object();
//    json_t *json = json_object();
//    json_t *users_array = json_array();
//
//
//
//    t_test *t = malloc(sizeof(t_test));
//    t->test = strdup("17");
//    t->nick = strdup("nick777");
//    t->next = NULL;
//    t->next = malloc(sizeof(t_test));
//    t->next->test = strdup("18");
//    t->next->nick = strdup("nick888");
//    t->next->next = NULL;
//
//    json_object_set_new(json, "chat_type", json_string("private"));
//    for (t_test *h = t; h; h = h->next) {
//        json_object_set_new(chat, "user_id", json_string(h->test));
//        json_object_set_new(chat, "user_nick", json_string(h->nick));
//        json_array_append_new(users_array, chat);
//        chat = json_object();
//    }
//
////    json_object_set_new(json, "chat_id", json_string("1"));
//    json_object_set_new(json, "type", json_string("new_chat"));
////    json_object_set_new(json, "new_chat", chat);
//    json_object_set_new(json, "users", users_array);
//
//    new_chat = json_dumps(json, 0);
//    puts(new_chat);
//    check_route(new_chat, mgr.active_connections);
//    return 0;
    //------------------------------
//    char *send_msg;
//    json_t *message = json_object();
//    json_t *json = json_object();
//    json_object_set_new(message, "chat_id", json_string("1"));
//    json_object_set_new(message, "chat_type", json_string("public"));
//    json_object_set_new(message, "chat_name", json_string("chatik"));
//    json_object_set_new(message, "admin_id", json_string("1"));
//    json_object_set_new(message, "message_content", json_string("Test message"));
//    json_object_set_new(message, "message_owner_id", json_string("1"));
//    json_object_set_new(message, "msg_type", json_string("text"));
//    json_object_set_new(message, "time", json_string("2020"));
//
//    json_object_set_new(json, "type", json_string("send_message"));
//    json_object_set_new(json, "message", message);
//
//    send_msg = json_dumps(json, 0);
//    check_route(send_msg, mgr.active_connections);
////------------------------------

}
