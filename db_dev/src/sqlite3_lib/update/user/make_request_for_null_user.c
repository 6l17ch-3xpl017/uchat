#include "header_db_dev.h"

/**
 * @param request - pointer to string which function will change
 * @param id - id of user
 * @param column_in_db - column in database which user want to change
 */

void make_request_for_null_user(char **request, char *id, char *column_in_db) {
    *request = mx_strnew((int)strlen(id) + (int)strlen(column_in_db) + 35);
    strcpy(*request, "UPDATE Users SET ");
    strcat(*request, column_in_db);
    strcat(*request, "=NULL WHERE id='");
    strcat(*request, id);
    strcat(*request, "';");
}
