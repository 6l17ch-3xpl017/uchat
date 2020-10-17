#include "header_db_dev.h"

void print_chat_info(t_chat *Chat) {
    printf("id:            %s\n", Chat->chat_id);
    printf("chat name:     %s\n", Chat->chat_name);
    printf("admin id:      %s\n", Chat->admin_id);
    printf("chat photo:    %s\n", Chat->chat_photo);
    printf("option:        %s\n", (char *)Chat->option);
}
