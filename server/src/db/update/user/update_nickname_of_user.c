#include "header_db_dev.h"

static int check_new_nick (char *new_nickname) {
    int result;
    t_user *temp;
    temp = (t_user *)malloc(sizeof(t_user));
    temp->nickname = strdup(new_nickname);
    temp->ph_number = NULL;
    temp->email = NULL;
    result = check_valid_data_for_sign_up(temp);
    mx_strdel(&temp->nickname);
    free(temp);
    if (result == nickname_was_already_signed_up)
        return result;
    return 0;
}

/**
 * @brief This function takes information about user and changes his nickname by a new one.
 * Structure 'User' will be updated too.
 * @param User - structure with all data about user.
 * @param new_nickname - new nickname which was chosen by user.
 * @return 'nickname_and_password_can_not_be_null' if new_nickname = NULL.
 * @return 'nickname_was_already_signed_up' if nickname is unavailable.
 * @return 'can_not_open_db' if connection with database was lost.
 * @return 'request_failed' if request was failed.
 * @return 'success' if nickname was successfully updated.
 * @return 1 if user wasn't sign in
 */

int update_nickname_of_user(t_user *User, char *new_nickname) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    if (new_nickname == NULL)
        return nickname_and_password_can_not_be_null;

    if (check_new_nick(new_nickname) == nickname_was_already_signed_up)
        return nickname_was_already_signed_up;

    connect_to_db

    if (User->id)
        make_sql_request(&request, "UPDATE Users SET nickname = %s WHERE id = %s ;", new_nickname, User->id);
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
