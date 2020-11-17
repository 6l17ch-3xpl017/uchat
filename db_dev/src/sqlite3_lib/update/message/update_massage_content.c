#include "header_db_dev.h"

int update_message_content(t_message *Message, char *new_content) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    connect_to_db

    make_sql_request(&request, "UPDATE Messages SET message_content = %s WHERE message_id = %s ;", new_content, Message->message_id);
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

