//
// Created by Illia Marchenko on 9/25/20.
//

#include "header_db_dev.h"

static int callback(void *my_arg, int argc, char **argv, char **array) {
    int *result = (int *)my_arg;
    *result = argc;
    return 0;
}

/**
 * @brief - Function check if user in database
 * @param nickname - nickname of user who you wanna check
 * @return - TRUE if user in database and FALSE if not
 */

bool if_user_in_db(char *nickname) {
    sqlite3 *db;
    char *error = NULL;
    int result;
    char *request = NULL;
    int number_of_users_with_such_nick;
    bool in_db = false;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK) {
        printf("Can't open database\n");
        exit(1);
    }

    asprintf(&request, "SELECT id\n"
                       "FROM Users\n"
                       "WHERE nickname='%s';", nickname);

    result = sqlite3_exec(db, request, callback, &number_of_users_with_such_nick, &error);

    if (request)
        free(request);

    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }

    sqlite3_close(db);

    if (number_of_users_with_such_nick == 0)
        in_db = false;
    else
        in_db = true;

    return in_db;
}

