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

static void make_request(char **request, char *id, char *new_phone_number) {
    *request = mx_strnew((int)(strlen(id) + strlen(new_phone_number)) + 45);
    strcpy(*request, "UPDATE Users SET phone_number=\"");
    strcat(*request, new_phone_number);
    strcat(*request, "\" WHERE id=\"");
    strcat(*request, id);
    strcat(*request, "\";");
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
 */

int update_phone_number_of_user(t_user *User, char *new_phone_number) {
    sqlite3 *db;
    char *request = NULL;
    int result;
    if (new_phone_number)
        if (check_new_phone(new_phone_number) == phone_number_was_already_signed_up)
            return phone_number_was_already_signed_up;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    if (new_phone_number != NULL)
        make_request(&request, User->id, new_phone_number);
    else
        make_request_for_null_user(&request, User->id, "phone_number");
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;

    populate_User_struct(User);

    return success;
}
