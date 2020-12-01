#include "header_db_dev.h"

static int callback(void *my_arg, int argc, char **argv, char **column) {
    int *temp = (int *)my_arg;
    *temp = atoi(argv[0]);
    return 0;
}

char *get_chat_by_id(char *chatname) {
    sqlite3 *database;
    char *request;
    int chat_id = 0;

    make_sql_request(&request, "SELECT chat_id FROM Chats WHERE chat_name=%s", chatname);
    sqlite3_open("chat_database.db", &database);
    sqlite3_exec(database, request, callback, &chat_id, 0);
    sqlite3_close(database);
    free(request);
    if (chat_id == 0)
        return NULL;
    return mx_itoa(chat_id);
}
