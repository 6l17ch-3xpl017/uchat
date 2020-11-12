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


//    add_chat_to_db(chat_struct_filling_with_null());


    ns_bind(&mgr, "7777", ev_handler, NULL);

    printf("Starting server on port: %s\n", "7777");

    for (;;)
        ns_mgr_poll(&mgr, 1000);

    ns_mgr_free(&mgr);

    return 0;
}