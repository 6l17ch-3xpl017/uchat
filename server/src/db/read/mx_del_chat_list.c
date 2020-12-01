#include "header_db_dev.h"

static void del_node(t_chat *list);

void mx_del_chat_list(t_chat *list, int leng) {
    if (leng == 2) {
        del_node(list->next);
        del_node(list);
        free(list);
        return;
    }
    for (int i = 0; i < leng; i++)
        mx_pop_back_for_chat(&list);
    free(list);
}

static void del_node(t_chat *list) {
    t_chat *temp = list;
    if (temp->chat_id)
        mx_strdel(&temp->chat_id);
    if (temp->chat_name)
        mx_strdel(&temp->chat_name);
    if (temp->admin_id)
        mx_strdel(&temp->admin_id);
    if (temp->chat_photo)
        mx_strdel(&temp->chat_photo);
    if (temp->option)
        mx_strdel((char **)(&temp->option));
    free(temp->next);
    temp->next = NULL;
}

