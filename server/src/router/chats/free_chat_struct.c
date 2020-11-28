#include "server.h"

void free_chat_struct(t_chat *Chat) {
    if (Chat->chat_id)
        mx_strdel(&Chat->chat_id);
    if (Chat->chat_name)
        mx_strdel(&Chat->chat_name);
    if (Chat->chat_photo)
        mx_strdel(&Chat->chat_photo);
    if (Chat->admin_id)
        mx_strdel(&Chat->admin_id);
//    if (Chat->option)
//        mx_strdel(&Chat->option);
    free(Chat);
}
