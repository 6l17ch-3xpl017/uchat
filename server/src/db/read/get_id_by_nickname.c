#include "header_db_dev.h"

static int callback(void *my_arg, int argc, char **argv, char **column) {
    int *temp = (int *)my_arg;
    *temp = atoi(argv[0]);
    return 0;
}

char *get_id_by_nickname(char *nickname) {
    sqlite3 *database;
    char *request;
    int id = 0;

    make_sql_request(&request, "SELECT id FROM Users WHERE nickname=%s", nickname);
    sqlite3_open("chat_database.db", &database);
    sqlite3_exec(database, request, callback, &id, 0);
    sqlite3_close(database);
    free(request);
    if (id == 0)
        return NULL;
    return mx_itoa(id);
}
