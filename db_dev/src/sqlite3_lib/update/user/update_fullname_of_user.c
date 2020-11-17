#include "header_db_dev.h"

/**
 * @brief This function takes information about user and changes his fullname by a new one.
 * Structure 'User' will be updated too.
 * @param User - structure with all data about user.
 * @param new_fullname - new fullname which was chosen by user.
 * @return 'can_not_open_db' if connection with database was lost.
 * @return 'request_failed' if request was failed.
 * @return 'success' if fullname was successfully updated.
 * @return 1 if user wasn't sign in
 */

int update_fullname_of_user(t_user *User, char *new_fullname) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    connect_to_db

    if (User->id)
        make_sql_request(&request, "UPDATE Users SET fullname = %s WHERE id = %s ;", new_fullname, User->id);
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
