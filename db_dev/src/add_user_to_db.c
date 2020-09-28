//
// Created by Illia Marchenko on 9/27/20.
//

#include "../inc/header_db_dev.h"

/**
 * @brief Function takes structure with data and paste this data into database. Every variable of structure User must be
 * NULL or must contain some information about user.
 * @param User - structure that has data about user (nickname, password, email, age, fullname, phone_number, user_photo,
 * options). Nickname and password can't be NULL.
 */

void add_user_to_db(t_user *User) {
    int result;
    sqlite3 *db;
    char *error = NULL;
    char *request = NULL;
    asprintf(&request, "INSERT INTO Users (nickname, password, email, age, fullname, phone_number, user_photo, options)"
                       "VALUES ('%s', '%s', ", User->nickname, User->password);
    if (User->email) {
        request = realloc(request, strlen(request) + strlen(User->email) + strlen("'', "));
        request = strcat(request, "'");
        request = strcat(request, User->email);
        request = strcat(request, "', ");
    }
    else {
        request = realloc(request, strlen(request) + strlen("NULL, "));
        request = strcat(request, "NULL, ");
    }

    if (User->age) {
        request = realloc(request, strlen(request) + strlen(User->age) + strlen("'', "));
        request = strcat(request, "'");
        request = strcat(request, User->age);
        request = strcat(request, "', ");
    }
    else {
        request = realloc(request, strlen(request) + strlen("NULL, "));
        request = strcat(request, "NULL, ");
    }

    if (User->fullname) {
        request = realloc(request, strlen(request) + strlen(User->fullname) + strlen("'', "));
        request = strcat(request, "'");
        request = strcat(request, User->fullname);
        request = strcat(request, "', ");
    }
    else {
        request = realloc(request, strlen(request) + strlen("NULL, "));
        request = strcat(request, "NULL, ");
    }

    if (User->ph_number) {
        request = realloc(request, strlen(request) + strlen(User->ph_number) + strlen("'', "));
        request = strcat(request, "'");
        request = strcat(request, User->ph_number);
        request = strcat(request, "', ");
    }
    else {
        request = realloc(request, strlen(request) + strlen("NULL, "));
        request = strcat(request, "NULL, ");
    }

    if (User->user_photo) {
        request = realloc(request, strlen(request) + strlen(User->user_photo) + strlen("'', "));
        request = strcat(request, "'");
        request = strcat(request, User->user_photo);
        request = strcat(request, "', ");
    }
    else {
        request = realloc(request, strlen(request) + strlen("NULL, "));
        request = strcat(request, "NULL, ");
    }

    if (User->option) {
        request = realloc(request, strlen(request) + strlen(User->option) + strlen("'');"));
        request = strcat(request, "'");
        request = strcat(request, User->option);
        request = strcat(request, "');");
    }
    else {
        request = realloc(request, strlen(request) + strlen("NULL);"));
        request = strcat(request, "NULL);");
    }

    // ----------------------------adding to the database----------------------------
    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK) {
        printf("Can't open database\n");
        exit(1);
    }

    result = sqlite3_exec(db, request, 0, 0, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }
    sqlite3_close(db);
    // -------------------------------------------------------------------------------

    if (request)
        free(request);
}
