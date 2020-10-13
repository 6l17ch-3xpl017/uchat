#include "header_db_dev.h"

static void make_request(char **request, char *id, char *new_pass) {
    *request = mx_strnew((int)(strlen(id) + strlen(new_pass)) + 41);
    strcpy(*request, "UPDATE Users SET password=\"");
    strcat(*request, new_pass);
    strcat(*request, "\" WHERE id=\"");
    strcat(*request, id);
    strcat(*request, "\";");
}

int update_password_of_user(t_user *User, char *new_password) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    if (new_password == NULL)
        return nickname_and_password_can_not_be_null;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    make_request(&request, User->id, new_password);
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;

    populate_User_struct(User);

    return success;
}
