#include "header_db_dev.h"

static void make_request(char **request, char *id, char *new_nickname) {
    *request = mx_strnew((int)(strlen(id) + strlen(new_nickname)) + 41);
    strcpy(*request, "UPDATE Users SET nickname=\"");
    strcat(*request, new_nickname);
    strcat(*request, "\" WHERE id=\"");
    strcat(*request, id);
    strcat(*request, "\";");
}

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
 */

int update_nickname_of_user(t_user *User, char *new_nickname) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    if (new_nickname == NULL)
        return nickname_and_password_can_not_be_null;

    if (check_new_nick(new_nickname) == nickname_was_already_signed_up)
        return nickname_was_already_signed_up;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    make_request(&request, User->id, new_nickname);
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;

    populate_User_struct(User);

    return success;
}
