#include "header_db_dev.h"


static void make_request(char **request, char *id, char *content) {
    *request = mx_strnew((int)strlen(id) + (int)strlen(content) + 2);
    strcpy(*request, content);
    strcat(*request, id);
    strcat(*request, "';");
}


int delete_chat_from_db(t_chat *Chat) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    if (!Chat->chat_id)
        return id_can_not_be_null;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    make_request(&request, Chat->chat_id, "DELETE FROM Chats WHERE chat_id='");

    result = sqlite3_exec(db, request, 0, 0, 0);

    mx_strdel(&request);
    sqlite3_close(db);

    if (result != SQLITE_OK)
        return request_failed;
    else
        return success;
}
