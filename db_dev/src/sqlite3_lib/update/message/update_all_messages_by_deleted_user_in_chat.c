#include "header_db_dev.h"

int update_all_messages_by_deleted_user_in_chat(t_chat *Chat, char *user_id) {
    sqlite3 *db;
    int result;
    char *request = NULL;
    char *new_user_id;

    connect_to_db

    new_user_id = mx_strnew((int)strlen(user_id) + 1);
    strcpy(new_user_id, "-");
    strcat(new_user_id, user_id);

    make_sql_request(&request, "UPDATE Messages SET message_owner_id = %s WHERE message_owner_id = %s "
                               "AND chat_id = %s ;",new_user_id, user_id, Chat->chat_id);
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&new_user_id);
    mx_strdel(&request);
    sqlite3_close(db);

    if (result != SQLITE_OK)
        return request_failed;

    return success;
}
