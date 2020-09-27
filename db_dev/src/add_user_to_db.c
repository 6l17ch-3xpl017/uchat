//
// Created by Illia Marchenko on 9/27/20.
//

/**
 * @brief function takes values for Users table and makes new writes to database
 * @param nickname - user's nickname (can't be NULL)
 * @param password - user's password (can't be NULL)
 * @param email - user's email (could be NULL)
 * @param age - user's age (could be NULL)
 * @param fullname - user's fullname (could be NULL)
 * @param phone_number - user's phone number (could be NULL)
 * @param user_photo - user's photo (could be NULL)
 * @param option - optional column (could be NULL)
 */

#include "header_db_dev.h"

void add_user_to_db(t_user *User) {
    int result;
    sqlite3 *db;
    char *error = NULL;
    char *request = NULL;
    asprintf(&request, "INSERT INTO Users (nickname, password, email, age, fullname, phone_number, user_photo, options)"
                       "VALUES ('%s', '%s', ", User->nickname, User->password);
    if (User->email) {
        realloc(request, strlen(request) + strlen(User->email) + strlen("'', "));
        request = strcat(request, "'");
        request = strcat(request, User->email);
        request = strcat(request, "', ");
    }
    else {
        realloc(request, strlen(request) + strlen("NULL, "));
        request = strcat(request, "NULL, ");
    }

    if (User->age) {
        realloc(request, strlen(request) + strlen(User->age) + strlen("'', "));
        request = strcat(request, "'");
        request = strcat(request, User->age);
        request = strcat(request, "', ");
    }
    else {
        realloc(request, strlen(request) + strlen("NULL, "));
        request = strcat(request, "NULL, ");
    }

    if (User->fullname) {
        realloc(request, strlen(request) + strlen(User->fullname) + strlen("'', "));
        request = strcat(request, "'");
        request = strcat(request, User->fullname);
        request = strcat(request, "', ");
    }
    else {
        realloc(request, strlen(request) + strlen("NULL, "));
        request = strcat(request, "NULL, ");
    }

    if (User->ph_number) {
        realloc(request, strlen(request) + strlen(User->ph_number) + strlen("'', "));
        request = strcat(request, "'");
        request = strcat(request, User->ph_number);
        request = strcat(request, "', ");
    }
    else {
        realloc(request, strlen(request) + strlen("NULL, "));
        request = strcat(request, "NULL, ");
    }

    if (User->user_photo) {
        realloc(request, strlen(request) + strlen(User->user_photo) + strlen("'', "));
        request = strcat(request, "'");
        request = strcat(request, User->user_photo);
        request = strcat(request, "', ");
    }
    else {
        realloc(request, strlen(request) + strlen("NULL, "));
        request = strcat(request, "NULL, ");
    }

    if (User->option) {
        realloc(request, strlen(request) + strlen(User->option) + strlen("'');"));
        request = strcat(request, "'");
        request = strcat(request, User->option);
        request = strcat(request, "');");
    }
    else {
        realloc(request, strlen(request) + strlen("NULL);"));
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
