#include "header_db_dev.h"

static int callback(void *my_arg, int argc, char **argv, char **columns) {
    int *result  = (int *)my_arg;
    *result = atoi(argv[0]);
    return 0;
}

int get_number_of_users_in_chat(t_chat *Chat) {
    int result;
    int number_of_users;
    char *request = NULL;
    sqlite3 *db;

    connect_to_db

    make_sql_request(&request, "SELECT COUNT(user_id) FROM Chat_User WHERE chat_id = %s ;", Chat->chat_id);
    result = sqlite3_exec(db, request, callback, &number_of_users, 0);
    mx_strdel(&request);
    sqlite3_close(db);

    if (result != SQLITE_OK)
        return -1;

    sqlite3_close(db);
    return number_of_users;
}

