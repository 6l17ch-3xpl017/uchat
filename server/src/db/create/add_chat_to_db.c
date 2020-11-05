#include "header_db_dev.h"

/**
 * @author Ilay Marchenko
 * @brief Function add chat into table 'Chats' in database. Every variable of structure User must be NULL or must
 *        contain some information about user.
 * @param Chat - structure that has data about chat (chat_name, admin_id, chat_photo, options). Chat_name and admin_id
 *        can't be NULL.
 */

int add_chat_to_db(t_chat *Chat) {
    int result;
    sqlite3 *db;
    char *request = NULL;

    if (!Chat->chat_name || !Chat->admin_id)
        return chat_name_and_admin_id_can_not_be_null;

    request = make_sql_request(&request, "INSERT INTO Chats (chat_name, admin_id, chat_photo, options) VALUES "
                                         "(%s, %s, %s, %s);", Chat->chat_name, Chat->admin_id, Chat->chat_photo,
                                         Chat->option);

    // ----------------------------adding to the database----------------------------
    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK) {
        mx_strdel(&request);
        return can_not_open_db;
    }

    result = sqlite3_exec(db, request, 0, 0, 0);
    if (result != SQLITE_OK) {
        mx_strdel(&request);
        return can_not_add_to_database;
    }
    sqlite3_close(db);
    // -------------------------------------------------------------------------------

    add_id_to_struct_Chat(Chat);

    if (request)
        free(request);

    return successfully_added_to_db;
}
