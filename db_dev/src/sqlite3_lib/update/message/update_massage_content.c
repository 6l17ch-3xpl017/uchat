#include "header_db_dev.h"

static void make_request(char **request, char *new_content, char *id) {
    *request = mx_strnew((int)(strlen(new_content) + 1000000));
    strcpy(*request, "UPDATE Messages SET message_content='");
    strcat(*request, new_content);
    strcat(*request, "' WHERE message_id='");
    strcat(*request, id);
    strcat(*request, "';");
}

int update_message_content(t_message *Message, char *new_content) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    make_request(&request, new_content, Message->message_id);
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;

    if (Message->message_content)
        mx_strdel(&Message->message_content);
    Message->message_content = strdup(new_content);
    return success;
}

