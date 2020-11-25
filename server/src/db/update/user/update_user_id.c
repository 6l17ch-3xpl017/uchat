#include "header_db_dev.h"

int update_user_id(t_user *User) {
    sqlite3 *db;
    char *request = NULL;
    int result;
    char *new_user_id;

    connect_to_db

    new_user_id = mx_strnew((int)strlen(User->id) + 1);
    strcpy(new_user_id, "-");
    strcat(new_user_id, User->id);

    make_sql_request(&request, "UPDATE Users SET id = %s WHERE id = %s ;", new_user_id, User->id);
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&new_user_id);
    mx_strdel(&request);
    sqlite3_close(db);

    if (result != SQLITE_OK)
        return request_failed;

    return success;
}
