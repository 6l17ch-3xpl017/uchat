#include "header_db_dev.h"

static void make_request(char **request, char *id, char *new_email) {
    *request = mx_strnew((int)(strlen(id) + strlen(new_email)) + 40);
    strcpy(*request, "UPDATE Users SET age=\"");
    strcat(*request, new_email);
    strcat(*request, "\" WHERE id=\"");
    strcat(*request, id);
    strcat(*request, "\";");
}

/**
 * @brief This function takes information about user and changes his age by a new one.
 * Structure 'User' will be updated too.
 * @param User - structure with all data about user.
 * @param new_age - new age which was chosen by user.
 * @return 'can_not_open_db' if connection with database was lost.
 * @return 'request_failed' if request was failed.
 * @return 'success' if age was successfully updated.
 */

int update_age_of_user(t_user *User, char *new_age) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    if (new_age != NULL)
        make_request(&request, User->id, new_age);
    else
        make_request_for_null_user(&request, User->id, "age");

    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;

    populate_User_struct(User);

    return success;
}
