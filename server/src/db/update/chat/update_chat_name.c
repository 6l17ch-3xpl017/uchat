#include "header_db_dev.h"

/**
 * @param Chat - structure with information about chat
 * @param new_chat_name - new name of chat
 * @return 'chat_name_can_not_be_null' if new_chat_name = NULL
 * @return 'chat_does_not_exist' if struct Chat = NULL or chat_id = NULL
 * @return 'can_not_open_db' if connection with database was lost
 * @return 'request_failed' if response to database was failed
 * @return 'success' if chat name was updated without troubles
 */

int update_chat_name(t_chat *Chat, char *new_chat_name) {
    sqlite3 *db;
    char *request = NULL;
    int result;

//  check arguments
    if (!new_chat_name)
        return chat_name_can_not_be_null;
    if (!Chat || !Chat->chat_id)
        return chat_does_not_exist;

//  open db
    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

//  make and send response
    make_sql_request(&request, "UPDATE Chats SET chat_name = %s WHERE chat_id = %s ;", new_chat_name, Chat->chat_id);
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    refresh_data_after_chat_update(Chat, db);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;
    return success;
}
