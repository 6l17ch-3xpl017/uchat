#include "header_db_dev.h"

static int check_new_email (char *new_email) {
    int result;
    t_user *temp;
    temp = (t_user *)malloc(sizeof(t_user));
    temp->nickname = NULL;
    temp->ph_number = NULL;
    temp->email = strdup(new_email);
    result = check_valid_data_for_sign_up(temp);
    mx_strdel(&temp->email);
    free(temp);
    if (result == email_was_already_signed_up)
        return result;
    return 0;
}

/**
 * @brief This function takes information about user and changes his email by a new one.
 * Structure 'User' will be updated too.
 * @param User - structure with all data about user.
 * @param new_email - new email which was chosen by user.
 * @return 'email_was_already_signed_up' if email is unavailable.
 * @return 'can_not_open_db' if connection with database was lost.
 * @return 'request_failed' if request was failed.
 * @return 'success' if email was successfully updated.
 * @return 1 if user wasn't sign in
 */

int update_email_of_user(t_user *User, char *new_email) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    if (new_email)
        if (check_new_email(new_email) == email_was_already_signed_up)
            return email_was_already_signed_up;

    connect_to_db

    if (User->id)
        make_sql_request(&request, "UPDATE Users SET email = %s WHERE id = %s ;", new_email, User->id);
    else
        return 1;
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;

    return success;
}

