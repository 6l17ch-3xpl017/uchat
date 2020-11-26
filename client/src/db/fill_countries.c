#include "db.h"

static int callback(void *my_arg, int argc, char **argv, char **columns) {
    int *res = (int *)my_arg;
    *res = argc;
    return 0;
}

bool check_country(sqlite3 *db)
{
    int result_of_request = 0;
    sqlite3_exec(db, "SELECT * FROM Countries WHERE country_name = 'Ukraine';", callback, &result_of_request, 0);
    if (result_of_request == 0)
        return false;
    return true;
}


int fill_countries()
{
    sqlite3 *db;
    int result;

    connect_to_db

    if (!check_country(db)) {
        sqlite3_close(db);
        return 420;
    }


}