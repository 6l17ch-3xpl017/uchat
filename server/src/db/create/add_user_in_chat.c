#include "header_db_dev.h"

/**
 * @brief Function takes structure with data and paste this data into database. Every variable of structure User must be
 * NULL or must contain some information about user.
 * @param User - structure that has data about user (nickname, password, email, age, fullname, phone_number, user_photo,
 * options). Nickname and password can't be NULL.
 * @return 'can_not_open_db' if connection to database was lost
 * @return 'can_not_add_to_database' if request to add new use to database was failed
 * @return 'successfully_added_to_db' if new user was successfully added to database
 */

int add_user_in_chat(t_user *User, t_chat *Chat) {
    int result;
    sqlite3 *db;
    char *request = NULL;

    connect_to_db
    // ----------------------------adding to the database---------------------------------------------
    for (t_user *current_node = User; current_node; current_node = current_node->next) {
        request = make_sql_request(&request, "INSERT INTO Chat_User (chat_id, user_id) VALUES (%s, %s);",
                                   Chat->chat_id, current_node->id);
        result = sqlite3_exec(db, request, 0, 0, 0);
        mx_strdel(&request);
        if (result != SQLITE_OK) {
            sqlite3_close(db);
            return can_not_add_to_database;
        }
    }
    // -----------------------------------------------------------------------------------------------
    sqlite3_close(db);
    return successfully_added_to_db;
}
