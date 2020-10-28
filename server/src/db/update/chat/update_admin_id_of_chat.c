#include "header_db_dev.h"

static void make_request(char **request, char *id, char *new_admin_id) {
    *request = mx_strnew((int)sizeof(char) * ((int)strlen(id) + (int)strlen(new_admin_id) + 50));
    *request = strcpy(*request, "UPDATE Chats SET admin_id='");
    *request = strcat(*request, new_admin_id);
    *request = strcat(*request, "' WHERE chat_id='");
    *request = strcat(*request, id);
    *request = strcat(*request, "';");
}

/**
 * @param Chat - structure with information about chat
 * @param new_admin_id - new id of chat's admin
 * @return 'admin_id_can_not_be_null' if new_admin_id = NULL
 * @return 'chat_does_not_exist' if struct Chat = NULL or chat_id = NULL
 * @return 'can_not_open_db' if connection with database was lost
 * @return 'request_failed' if request to database was failed
 * @return 'success' if chat name was updated without troubles
 */

int update_admin_id_of_chat(t_chat *Chat, char *new_admin_id) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    //  check arguments
    if (!new_admin_id)
        return admin_id_can_not_be_null;
    if (!Chat || !Chat->chat_id)
        return chat_does_not_exist;

//  open db
    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

//  make and send request
    make_request(&request, Chat->chat_id, new_admin_id);
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    refresh_data_after_chat_update(Chat, db);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;
    return success;
}
