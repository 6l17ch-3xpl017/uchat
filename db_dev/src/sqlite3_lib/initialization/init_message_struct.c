#include "header_db_dev.h"

void init_message_struct(t_message *Message) {
    Message->message_id         = NULL;
    Message->message_owner_id   = NULL;
    Message->message_owner_name = NULL;
    Message->chat_id            = NULL;
    Message->type               = NULL;
    Message->message_content    = NULL;
    Message->time               = NULL;
    Message->next               = NULL;
    Message->option             = NULL;
    Message->changed            = 0;
    Message->deleted            = 0;
}
