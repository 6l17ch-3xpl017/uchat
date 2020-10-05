#include "header_db_dev.h"

static int callback_number_of_email_or_nickname(void *my_arg, int argc, char **argv, char **array) {
    int *result = (int *)my_arg;
    *result = argc;
    return 0;
}

static int callback_to_get_password(void *my_arg, int argc, char **argv, char **array) {
    t_password *temp = my_arg;
    temp->password = strdup(argv[0]);
    return 0;
}

/**
 * @author Ilay Marchenko
 * @brief This function takes struct 'User', where we have nickname or email of user and his password, check it
 *        and return message of search result. If user was already registered, calls function 'populate_User_struct'
 *        which copy all data from database to struct.
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
    char *request = NULL;
    int number_of_users_with_such_nick_or_email = 0;
    t_password *password = malloc(sizeof(t_password));

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK) {
        printf("Can't open database\n");
        exit(1);
    }

    if (User->nickname) {
        request = (char *)malloc(sizeof(char) * (39 + strlen(User->nickname)));
        request = strcpy(request, "SELECT id FROM Users WHERE nickname='");
        request = strcat(request, User->nickname);
        request = strcat(request, "';");
    }
    else if (User->email) {
        request = (char *)malloc(sizeof(char) * (36 + strlen(User->email)));
        request = strcpy(request, "SELECT id FROM Users WHERE email='");
        request = strcat(request, User->email);
        request = strcat(request, "';");
    }
    else {
        sqlite3_close(db);
        free(password);
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
        free(password);
        return "Login incorrect";
    }

    if (request)
        free(request);

    if (User->nickname) {
        request = (char *)malloc(sizeof(char) * (45 + strlen(User->nickname)));
        request = strcpy(request, "SELECT password FROM Users WHERE nickname='");
        request = strcat(request, User->nickname);
        request = strcat(request, "';");
    }
    else if (User->email) {
        request = (char *)malloc(sizeof(char) * (42 + strlen(User->email)));
        request = strcpy(request, "SELECT password FROM Users WHERE email='");
        request = strcat(request, User->email);
        request = strcat(request, "';");
    }
    result = sqlite3_exec(db, request, callback_to_get_password, password, &error1);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error1);
    }
    if (password->password) {
        if (strcmp(password->password, User->password) == 0) {
            free(password->password);
            free(password);
            free(request);
            sqlite3_close(db);
            populate_User_struct(User);
            return "Login and password correct";
        }
        else {
            free(password->password);
            free(password);
            free(request);
            sqlite3_close(db);
            return "Password incorrect";
        }
    }

    sqlite3_close(db);
    free(password);

    if (request)
        free(request);

    return "Function fail";
}

