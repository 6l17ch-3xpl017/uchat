#include "header_db_dev.h"

int delete_user(t_user *User) {
    sqlite3 *db;
    int result;
    char *request = NULL;

    if (!User->id)
        return id_can_not_be_null;

    connect_to_db

    make_sql_request(&request, "DELETE FROM Users WHERE id=%s;", User->id);
    result = sqlite3_exec(db, request, 0, 0, 0);
    mx_strdel(&request);
    sqlite3_close(db);

    if (result != SQLITE_OK)
        return request_failed;
    else
        return success;
}
