#include "header_db_dev.h"

/**
 * @brief Function takes structure with data and paste this data into database. Every variable of structure Message must be
 * NULL or must contain some information about message.
 * @param Message - structure that has data about the message (message_id, message_owner_id, chat_id, message_content,
 * time, changed, options). message_id, message_owner_id and chat_id can't be NULL.
 * @return 'can_not_open_db' if connection to database was lost
 * @return 'can_not_add_to_database' if request to add new use to database was failed
 * @return 'successfully_added_to_db' if new user was successfully added to database
 */

int add_message_to_db(t_message *Message) {
    int result;
    sqlite3 *db;
    char *request = NULL;

    connect_to_db

    // ----------------------------check if nickname and password not NULL-----------------------------
    if (!Message->message_content)
        return message_cannot_be_empty;
    // -----------------------------------making request-----------------------------------------------
    char *time_str = mx_itoa(Message->time);
    char *change_str = mx_itoa(Message->changed);
    char *delete_str = mx_itoa(Message->deleted);
    make_sql_request(&request, "INSERT INTO Messages (message_owner_id, message_owner_name, chat_id, message_content, time, changed, deleted, type,"
                               " options) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s);", Message->message_owner_id,
                     Message->message_owner_name, Message->message_content, Message->chat_id, time_str, change_str,
                     delete_str, Message->type, (char *)Message->option);
    mx_strdel(&time_str);
    mx_strdel(&change_str);
    mx_strdel(&delete_str);
    // ----------------------------adding to the database---------------------------------------------
    char *err_tmp = mx_strnew(1000);
    result = sqlite3_exec(db, request, 0, 0, &err_tmp);
    if (result != SQLITE_OK) {
        puts(err_tmp);
        sqlite3_close(db);
        mx_strdel(&request);
        return can_not_add_to_database;
    }
    sqlite3_close(db);
    // ------------------------------------------------------------------------------------------------
    add_id_to_struct_Message(Message);
    if (request)
        free(request);
    return successfully_added_to_db;
}


