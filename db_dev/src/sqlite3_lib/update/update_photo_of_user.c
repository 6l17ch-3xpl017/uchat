#include "header_db_dev.h"

static void make_request_for_null(char **request, char *id) {
    *request = mx_strnew((int)strlen(id) + 44);
    strcpy(*request, "UPDATE Users SET user_photo=NULL WHERE id=\"");
    strcat(*request, id);
    strcat(*request, "\";");
}

static void make_request(char **request, char *id, char *new_photo) {
    *request = mx_strnew((int)(strlen(id) + strlen(new_photo)) + 50);
    strcpy(*request, "UPDATE Users SET user_photo=\"");
    strcat(*request, new_photo);
    strcat(*request, "\" WHERE id=\"");
    strcat(*request, id);
    strcat(*request, "\";");
}

int update_photo_of_user(t_user *User, char *new_photo) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    if (new_photo != NULL)
        make_request(&request, User->id, new_photo);
    else
        make_request_for_null(&request, User->id);

    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    sqlite3_close(db);
    if (result != SQLITE_OK)
        return request_failed;

    populate_User_struct(User);

    return success;
}
