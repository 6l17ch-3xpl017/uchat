#include "client.h"

/**
 * @author Illia Marchenko
 * @brief Function creates database if database wasn't created before and creates all tables if they weren't created yet.
 * @name 'init_database' - because we should call it everytime before chat turning on to be sure that with database everything fine.
 */
int init_local_database() {
    sqlite3 *db;
    int result;

    result = sqlite3_open("local.db", &db);

    if (result != SQLITE_OK)
        return 404;

    // -----------------------------=-Block to create Users table-=-------------------------------
    result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS \"Countries\" (\n"
                              "\t\"country_name\"\tTEXT NOT NULL,\n"
                              "\t\"country_flag\"\tTEXT NOT NULL\n"
                              ");", 0, 0, 0);

    if (result != SQLITE_OK) {
        sqlite3_close(db);
        return 404;
    }
    // -------------------------------------------------------------------------------------------

    sqlite3_close(db);
    return 420;
}
