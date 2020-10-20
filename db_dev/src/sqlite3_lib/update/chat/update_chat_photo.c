#include "header_db_dev.h"

static void make_request(char **request, char *id, char *new_photo_of_chat) {
    *request = mx_strnew((int)sizeof(char) * ((int)strlen(id) + (int)strlen(new_photo_of_chat) + 55));
    *request = strcpy(*request, "UPDATE Chats SET chat_photo='");
    *request = strcat(*request, new_photo_of_chat);
    *request = strcat(*request, "' WHERE chat_id='");
    *request = strcat(*request, id);
    *request = strcat(*request, "';");
}

static void make_request_for_null(char **request, char *id) {
    *request = mx_strnew((int)(sizeof(char) * (strlen(id) + 55)));
    strcpy(*request, "UPDATE Chats SET chat_photo=NULL WHERE chat_id='");
    strcat(*request, id);
    strcat(*request, "';");
}

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
//  open db
    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;
//  make and send request
    if (new_photo_of_chat)
        make_request(&request, Chat->chat_id, new_photo_of_chat);
    else
        make_request_for_null(&request, Chat->chat_id);
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    refresh_data_after_chat_update(Chat, db);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;
    return success;
}
