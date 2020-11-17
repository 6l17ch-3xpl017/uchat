#include "header_db_dev.h"

/**
 * @param Chat - structure with information about chat
 * @param new_photo_of_chat - new photo of chat
 * @return 'chat_does_not_exist' if struct Chat = NULL or chat_id = NULL
 * @return 'can_not_open_db' if connection with database was lost
 * @return 'request_failed' if request to database was failed
 * @return 'success' if chat name was updated without troubles
 */

int update_chat_photo(t_chat *Chat, char *new_photo_of_chat) {
    sqlite3 *db;
    char *request = NULL;
    int result;

//  check arguments
    if (!Chat || !Chat->chat_id)
        return chat_does_not_exist;

    connect_to_db

//  make and send request
    make_sql_request(&request, "UPDATE Chats SET chat_photo = %s WHERE chat_id = %s ;", new_photo_of_chat, Chat->chat_id);
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    refresh_data_after_chat_update(Chat, db);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;
    return success;
}
