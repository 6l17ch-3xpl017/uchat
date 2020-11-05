#include "header_db_dev.h"

static int callback(void *my_arg, int argc, char **argv, char **column) {
    t_user *temp = (t_user *)my_arg;
    temp->id = strdup(argv[0]);
    return 0;
}

void add_id_to_struct_User(t_user *User) {
    sqlite3 *database;
    char *request;
    make_sql_request(&request, "SELECT id FROM Users WHERE nickname=%s", User->nickname);
    sqlite3_open("chat_database.db", &database);
    sqlite3_exec(database, request, callback, User, 0);
    sqlite3_close(database);
    free(request);
}
