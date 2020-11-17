#include "header_db_dev.h"

int change_admin_randomly(t_chat *Chat) {
    sqlite3 *db;
    int result;
    char *request = NULL;
    char **list_of_users_id = (char **)malloc(sizeof(char *) * Chat->number_of_users);
    t_user *cursor = Chat->user_in_chat;

    for (int i = 0; i < Chat->number_of_users; i++) {
        list_of_users_id[i] = strdup(cursor->id);
        cursor = cursor->next;
    }

    connect_to_db


}
