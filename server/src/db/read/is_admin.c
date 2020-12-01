#include "header_db_dev.h"

static int callback(void *my_arg, int argc, char **argv, char **columns) {
    int *result = (int *)my_arg;
    *result = atoi(argv[0]);
    return 0;
}

int is_admin(t_user *User, t_chat *Chat) {
    sqlite3 *db;
    int result;
    int numbers_of_chat;
    char *request = NULL;

    connect_to_db

    make_sql_request(&request, "SELECT COUNT(chat_id) FROM Chats WHERE admin_id = %s AND chat_id = %s ;",
                     User->id, Chat->chat_id);
    result = sqlite3_exec(db, request, callback, &numbers_of_chat, 0);
    mx_strdel(&request);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;
    if (numbers_of_chat != 0)
        return 1;
    else
        return 0;
}
