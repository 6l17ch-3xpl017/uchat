#include "header_db_dev.h"

static int send_request(sqlite3 *db, char *request_content, char *chat_id) {
    char *request = NULL;
    int result;

    make_sql_request(&request, request_content, chat_id);
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    return result;
}

int delete_chat_from_db(t_chat *Chat) {
    sqlite3 *db;
    int result;

    if (!Chat->chat_id)
        return id_can_not_be_null;

    connect_to_db

    result += send_request(db, "DELETE FROM Chat_User WHERE chat_id = %s ;", Chat->chat_id);
    result += send_request(db, "DELETE FROM Messages WHERE chat_id = %s ;", Chat->chat_id);
    result += send_request(db, "DELETE FROM Chats WHERE chat_id = %s ;", Chat->chat_id);
    sqlite3_close(db);

    if (result != SQLITE_OK)
        return request_failed;
    else
        return success;
}

