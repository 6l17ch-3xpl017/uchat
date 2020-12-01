#include "header_db_dev.h"

static void free_and_dup(char **a, char *b) {
    if (*a)
        free(*a);
    if (b)
        *a = strdup(b);
    else
        *a = NULL;
}

static int callback(void *my_arg, int argc, char **argv, char **columns) {
    t_chat *temp = (t_chat *)my_arg;
    free_and_dup(&temp->chat_id,               argv[0]);
    free_and_dup(&temp->chat_name,             argv[1]);
    free_and_dup(&temp->admin_id,              argv[2]);
    free_and_dup(&temp->chat_photo,            argv[3]);
    free_and_dup((char **)(&temp->option),     argv[4]);
    return 0;
}

void refresh_data_after_chat_update(t_chat *Chat, sqlite3 *db) {
    char *request = NULL;
    make_sql_request(&request, "SELECT * FROM Chats WHERE chat_id = %s ;", Chat->chat_id);
    sqlite3_exec(db, request, callback, Chat, 0);
    mx_strdel(&request);
}
