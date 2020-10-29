#include "header_db_dev.h"

static int get_len_of_item(char *item) {
    int result = 5;
    if (item)
        return result + (int)strlen(item) + 4;
    else
        return result;
}


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
    // -----------------------------------making request-----------------------------------------------
    request = (char *)malloc(sizeof(char) * (get_len_of_item(User->id)+get_len_of_item(Chat->chat_id)+53));
    request = strcpy(request, "INSERT INTO Chat_User (chat_id, user_id) VALUES (");
    request = strcat(request, Chat->chat_id);
    request = strcat(request, ", ");
    request = strcat(request, User->id);
    request = strcat(request, ");");

    // ----------------------------adding to the database---------------------------------------------
    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK) {
        mx_strdel(&request);
        return can_not_open_db;
    }

    result = sqlite3_exec(db, request, 0, 0, 0);
    if (result != SQLITE_OK) {
        sqlite3_close(db);
        mx_strdel(&request);
        return can_not_add_to_database;
    }
    sqlite3_close(db);
    // ------------------------------------------------------------------------------------------------

    if (request)
        free(request);

    return successfully_added_to_db;
}
