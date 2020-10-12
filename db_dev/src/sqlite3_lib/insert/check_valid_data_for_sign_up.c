#include "header_db_dev.h"

static void make_request(char **request, char *data, char *content) {
    *request = mx_strnew((int)strlen(content) + (int)strlen(data) + 2);
    *request = strcpy(*request, content);
    *request = strcat(*request, data);
    *request = strcat(*request, "\";");
}

static int callback(void *my_arg, int argc, char **argv, char **columns) {
    int *res = (int *)my_arg;
    *res = argc;
    return 0;
}

static int send_request(char *request) {
    sqlite3 *db;
    int number_of_users = 0;
    char *error;
    sqlite3_open("chat_database.db", &db);
    int res = sqlite3_exec(db, request, callback, &number_of_users, &error);

    if (res != SQLITE_OK)
        sqlite3_free(error);

    mx_strdel(&request);

    sqlite3_close(db);

    if (number_of_users != 0)
        return 1;

    return 0;
}

/**
 * @brief Function check if someone in chat used such nickname, email or phone number before
 * @param User - structure with info about user who is singing up
 * @return 'success' if values of nickname, email, phone number - valid
 * @return 'nickname_was_already_signed_up' if some chat user has such nickname
 * @return 'email_was_already_signed_up' if some chat user has such email
 * @return 'phone_number_was_already_signed_up' if some chat user has such phone number
 */

int check_valid_data_for_sign_up(t_user *User) {
    char *request = NULL;
    if (User->nickname) {
        make_request(&request, User->nickname, "SELECT id FROM Users WHERE nickname=\"");
        if (send_request(request) == 1)
            return nickname_was_already_signed_up;
    }
    if (User->email) {
        make_request(&request, User->email, "SELECT id FROM Users WHERE email=\"");
        if (send_request(request) == 1)
            return email_was_already_signed_up;
    }
    if (User->ph_number) {
        make_request(&request, User->ph_number, "SELECT id FROM Users WHERE phone_number=\"");
        if (send_request(request) == 1)
            return phone_number_was_already_signed_up;
    }
    return success;
}
