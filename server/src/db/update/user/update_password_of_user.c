#include "header_db_dev.h"

/**
 * @brief This function takes information about user and change his password by a new one.
 * Structure 'User' will be updated too.
 * @param User - structure with all data about user.
 * @param new_password - new password which was chosen by user.
 * @return 'nickname_and_password_can_not_be_null' if new_password = NULL.
 * @return 'can_not_open_db' if connection with database was lost.
 * @return 'request_failed' if request was failed.
 * @return 'success' if password was successfully updated.
 * @return 1 if user wasn't sign in
 */

int update_password_of_user(t_user *User, char *new_password) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    if (new_password == NULL)
        return nickname_and_password_can_not_be_null;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    if (User->id)
        make_sql_request(&request, "UPDATE Users SET password = %s WHERE id = %s ;", new_password, User->id);
    else
        return 0;
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;

    populate_User_struct(User);

    return success;
}
