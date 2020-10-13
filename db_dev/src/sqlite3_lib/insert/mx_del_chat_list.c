#include "header_db_dev.h"

void mx_del_chat_list(t_chat *list, int leng) {
    for (int i = 0; i < leng; i++)
        mx_pop_back_for_chat(&list);
    free(list);
}
