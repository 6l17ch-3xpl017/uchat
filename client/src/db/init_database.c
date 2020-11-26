#include "db.h"

/**
 * @author Illia Marchenko
 * @brief Function creates database if database wasn't created before and creates all tables if they weren't created yet.
 * @name 'init_database' - because we should call it everytime before chat turning on to be sure that with database everything fine.
 */
int init_database() {
    sqlite3 *db;
    int result;

    connect_to_db

    // -----------------------------=-Block to create Users table-=-------------------------------
    result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS\"Countries\" (\n"
                              "\"country_name\"\tTEXT NOT NULL,\n"
                              "\"country_flag\"\tBLOB NOT NULL,\n"
                              "\"country_flag_size\"\tINTEGER NOT NULL,\n"
                              ");", 0, 0, 0);

    if (result != SQLITE_OK) {
        sqlite3_close(db);
        return 404;
    }
    // -------------------------------------------------------------------------------------------

    sqlite3_close(db);
    return 420;
}
