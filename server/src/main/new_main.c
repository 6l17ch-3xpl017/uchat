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
    struct iobuf *io = &nc->recv_iobuf;
    char *income_json = NULL;
    if (ev == NS_RECV)
    {
        income_json = strndup(io->buf, io->len);

        check_route(income_json, nc);
        iobuf_remove(io, io->len);
        free(income_json);
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
    init_database();


////    add_chat_to_db(chat_struct_filling_with_null());

    ns_bind(&mgr, "7777", ev_handler, NULL);

    printf("Starting server on port: %s\n", "7777");

    for (;;)
        ns_mgr_poll(&mgr, 1000);

    ns_mgr_free(&mgr);

    return 0;

    //------------------------------
//    char *send_msg;
//    json_t *message = json_object();
//    json_t *json = json_object();
//
//    json_object_set_new(message, "chat_id", json_string("1"));
//    json_object_set_new(message, "chat_name", json_string("chatik"));
//    json_object_set_new(message, "chat_type", json_string("public"));
//    json_object_set_new(message, "user_id", json_string("1"));
//    json_object_set_new(message, "time", json_string("2020"));
//
//    json_object_set_new(json, "type", json_string("open_chat"));
//    json_object_set_new(json, "chat", message);
//
//    send_msg = json_dumps(json, 0);
//    check_route(send_msg, mgr.active_connections);
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
