#include "header_db_dev.h"

static int callback(void *my_arg, int argc, char **argv, char **column) {
    t_chat *temp = (t_chat *)my_arg;
    temp->chat_id = strdup(argv[0]);
    return 0;
}

void add_id_to_struct_Chat(t_chat *Chat) {
    sqlite3 *database;
    char *request;

    make_sql_request(&request, "SELECT chat_id FROM Chats WHERE chat_name=%s", Chat->chat_name);
    sqlite3_open("chat_database.db", &database);
    sqlite3_exec(database, request, callback, Chat, 0);
    sqlite3_close(database);
    free(request);
}
