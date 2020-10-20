#include "header_db_dev.h"

static void make_request(char **request, char *id, char *new_photo) {
    *request = mx_strnew((int)(strlen(id) + strlen(new_photo)) + 50);
    strcpy(*request, "UPDATE Users SET user_photo=\"");
    strcat(*request, new_photo);
    strcat(*request, "\" WHERE id=\"");
    strcat(*request, id);
    strcat(*request, "\";");
}

/**
 * @brief This function takes information about user and changes his photo by a new one.
 * Structure 'User' will be updated too.
 * @param User - structure with all data about user.
 * @param new_photo - new photo which was chosen by user.
 * @return 'can_not_open_db' if connection with database was lost.
 * @return 'request_failed' if request was failed.
 * @return 'success' if age was successfully updated.
 * @return 0 if user wasn't sign in
 */

int update_photo_of_user(t_user *User, char *new_photo) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    if (User->id) {
        if (new_photo != NULL)
            make_request(&request, User->id, new_photo);
        else
            make_request_for_null_user(&request, User->id, "user_photo");
    }
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
