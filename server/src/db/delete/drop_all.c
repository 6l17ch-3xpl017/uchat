#include "server.h"

void drop_all() {
    int result;
    sqlite3 *db;
    char *error = NULL;

    sqlite3_open("chat_database.db", &db);
    result = sqlite3_exec(db, "DROP TABLE Messages;\n"
                              "DROP TABLE Chats;\n"
                              "DROP TABLE Users;\n"
                              "DROP TABLE Chat_User;", 0, 0, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }
    sqlite3_close(db);
}
