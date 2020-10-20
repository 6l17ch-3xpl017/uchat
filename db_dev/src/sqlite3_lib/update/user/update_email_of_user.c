#include "header_db_dev.h"

static void make_request(char **request, char *id, char *new_email) {
    *request = mx_strnew((int)(strlen(id) + strlen(new_email)) + 38);
    strcpy(*request, "UPDATE Users SET email=\"");
    strcat(*request, new_email);
    strcat(*request, "\" WHERE id=\"");
    strcat(*request, id);
    strcat(*request, "\";");
}

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
 */

int update_email_of_user(t_user *User, char *new_email) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    if (new_email)
        if (check_new_email(new_email) == email_was_already_signed_up)
            return email_was_already_signed_up;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    if (new_email)
        make_request(&request, User->id, new_email);
    else
        make_request_for_null_user(&request, User->id, "email");
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;

    populate_User_struct(User);

    return success;
}

