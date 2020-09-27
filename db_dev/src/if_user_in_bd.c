//
// Created by Illia Marchenko on 9/25/20.
//

#include "header_db_dev.h"

static int callback_number_of_email_or_nickname(void *my_arg, int argc, char **argv, char **array) {
    int *result = (int *)my_arg;
    *result = argc;
    return 0;
}

static int callback_to_get_password(void **my_arg, int argc, char **argv, char **array) {
    *my_arg = strdup(argv[0]);
    return 0;
}

/**
 * @author Ilay Marchenko
 * @brief This function takes struct User, where we have nickname or email of user and his password, check it
 *        and return message of search result
 * @param User struct that must contain email or nickname of user and his password.
 * @return - "User->nickname and User->email can't be NULL" if nickname and email are NULL.
 * @return - "Login incorrect" if nickname/email was not found in database.
 * @return - "Password incorrect" if nickname/email was found in database but password in database and in structure
 *            was different.
 * @return - "Login and password correct" if nickname/email was found in database and password in database and in
 *            structure was the same.
 * @return - "Function fail" can't be in any case. If this function returned this message - something went wrong.
 */

char *user_in_db(t_user *User) {
    sqlite3 *db;
    char *error = NULL;
    char *error1 = NULL;
    int result;
    char *password_from_db = NULL;
    char *request = NULL;
    int number_of_users_with_such_nick_or_email = 0;
    bool in_db = false;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK) {
        printf("Can't open database\n");
        exit(1);
    }

    if (User->nickname) {
        asprintf(&request, "SELECT id "
                           "FROM Users "
                           "WHERE nickname='%s';", User->nickname);
    }
    else if (User->email) {
        asprintf(&request, "SELECT id "
                           "FROM Users "
                           "WHERE email='%s';", User->email);
    }
    else {
        sqlite3_close(db);
        return "User->nickname and User->email can't be NULL";
    }

    result = sqlite3_exec(db, request, callback_number_of_email_or_nickname, &number_of_users_with_such_nick_or_email,
                          &error);

    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }

    if (number_of_users_with_such_nick_or_email == 0) {
        sqlite3_close(db);
        free(request);
        return "Login incorrect";
    }
    else
        in_db = true;

    if (request)
        free(request);

    if (in_db) {
        if (User->nickname) {
            asprintf(&request, "SELECT password "
                               "FROM Users "
                               "WHERE nickname='%s';", User->nickname);
        }
        else if (User->email) {
            asprintf(&request, "SELECT password "
                               "FROM Users "
                               "WHERE email='%s';", User->email);
        }
        result = sqlite3_exec(db, request, callback_to_get_password, &password_from_db, &error1);
        if (result != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", error);
            sqlite3_free(error1);
        }
        if (password_from_db) {
            if (strcmp(password_from_db, User->password) == 0) {
                free(password_from_db);
                free(request);
                sqlite3_close(db);
                return "Login and password correct";
            }
        }
        else {
            free(password_from_db);
            free(request);
            sqlite3_close(db);
            return "Password incorrect";
        }
    }

    sqlite3_close(db);

    if (request)
        free(request);

    return "Function fail";
}

