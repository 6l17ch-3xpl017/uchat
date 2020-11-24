#include "header_db_dev.h"

int change_admin_randomly(t_chat *Chat, char *current_admin) {
    int result;
    char **list_of_users_id = (char **)malloc(sizeof(char *) * Chat->number_of_users);
    t_user *cursor = Chat->user_in_chat;

    for (int i = 0; i < Chat->number_of_users; i++) {
        list_of_users_id[i] = strdup(cursor->id);
        cursor = cursor->next;
    }

    while (true) {
        random_number(0, Chat->number_of_users - 1)
        if (list_of_users_id[rand_num][0] != '-' && strcmp(list_of_users_id[rand_num], current_admin) != 0) {
            result = update_admin_id_of_chat(Chat, list_of_users_id[rand_num]);
            break;
        }
    }

    for (int j = 0; j < Chat->number_of_users; j++) {
        mx_strdel(&list_of_users_id[j]);
    }
    free(list_of_users_id);

    return result;
}
