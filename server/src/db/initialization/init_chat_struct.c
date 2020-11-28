#include "header_db_dev.h"

void init_chat_struct(t_chat *Chat) {
    Chat->chat_id = NULL;
    Chat->chat_name = NULL;
    Chat->chat_photo = NULL;
    Chat->admin_id = NULL;
    Chat->next = NULL;
    Chat->option = NULL;
    Chat->chat_type = NULL;
}
