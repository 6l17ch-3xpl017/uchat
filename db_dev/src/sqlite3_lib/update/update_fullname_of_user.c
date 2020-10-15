#include "header_db_dev.h"

static void make_request_for_null(char **request, char *id) {
    *request = mx_strnew((int)strlen(id) + 43);
    strcpy(*request, "UPDATE Users SET fullname=NULL WHERE id=\"");
    strcat(*request, id);
    strcat(*request, "\";");
}

static void make_request(char **request, char *id, char *new_fullname) {
    *request = mx_strnew((int)(strlen(id) + strlen(new_fullname)) + 41);
    strcpy(*request, "UPDATE Users SET fullname=\"");
    strcat(*request, new_fullname);
    strcat(*request, "\" WHERE id=\"");
    strcat(*request, id);
    strcat(*request, "\";");
}

int update_fullname_of_user(t_user *User, char *new_fullname) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    if (new_fullname)
        make_request(&request, User->id, new_fullname);
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
