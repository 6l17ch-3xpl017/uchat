#include "header_db_dev.h"

/**
 * @brief This function takes information about user and changes his age by a new one.
 * Structure 'User' will be updated too.
 * @param User - structure with all data about user.
 * @param new_age - new age which was chosen by user.
 * @return 'can_not_open_db' if connection with database was lost.
 * @return 'request_failed' if request was failed.
 * @return 'success' if age was successfully updated.
 * @return 1 if user wasn't sign in
 */

int update_age_of_user(t_user *User, char *new_age) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    if (User->id)
        make_sql_request(&request, "UPDATE Users SET age = %s WHERE id = %s ;", new_age, User->id);
    else
        return 1;
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;

    populate_User_struct(User);

    return success;
}
