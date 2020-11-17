#include "header_db_dev.h"

static int check_new_phone(char *new_phone_number) {
    int result;
    t_user *temp;
    temp = (t_user *)malloc(sizeof(t_user));
    temp->nickname = NULL;
    temp->ph_number = strdup(new_phone_number);
    temp->email = NULL;
    result = check_valid_data_for_sign_up(temp);
    mx_strdel(&temp->ph_number);
    free(temp);
    if (result == phone_number_was_already_signed_up)
        return result;
    return 0;
}

/**
 * @brief This function takes information about user and change his phone number by a new one.
 * Structure 'User' will be updated too.
 * @param User - structure with all data about user.
 * @param new_nickname - new nickname which was chosen by user.
 * @return 'phone_number_was_already_signed_up' if new phone number is unavailable.
 * @return 'can_not_open_db' if connection with database was lost.
 * @return 'request_failed' if request was failed.
 * @return 'success' if phone number was successfully updated.
 * @return 1 if user wasn't sign in
 */

int update_phone_number_of_user(t_user *User, char *new_phone_number) {
    sqlite3 *db;
    char *request = NULL;
    int result;
    if (new_phone_number)
        if (check_new_phone(new_phone_number) == phone_number_was_already_signed_up)
            return phone_number_was_already_signed_up;

    connect_to_db

    if (User->id)
        make_sql_request(&request, "UPDATE Users SET phone_number = %s WHERE id = %s ;", new_phone_number, User->id);
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
