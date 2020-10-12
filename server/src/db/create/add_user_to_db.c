#include "server.h"

static int get_len_of_item(char *item) {
    if (item)
        return (int)strlen(item) + 4;
    else
        return 6;
}

static int get_len_of_request(t_user *User) {
    int result = 112;
    result += get_len_of_item(User->nickname);
    result += get_len_of_item(User->password);
    result += get_len_of_item(User->email);
    result += get_len_of_item(User->age);
    result += get_len_of_item(User->fullname);
    result += get_len_of_item(User->ph_number);
    result += get_len_of_item(User->user_photo);
    result += get_len_of_item(User->option);
    return result;
}

static void concatenate_with_request(char **request, char *info) {
    static int counter = 0;
    if (counter == 5) {
        if (info) {
            *request = strcat(*request, "'");
            *request = strcat(*request, info);
            *request = strcat(*request, "');");
        }
        else
            *request = strcat(*request, "NULL);");
    }
    else {
        if (info) {
            *request = strcat(*request, "'");
            *request = strcat(*request, info);
            *request = strcat(*request, "', ");
        } else
            *request = strcat(*request, "NULL, ");
        counter++;
    }
}

/**
 * @brief Function takes structure with data and paste this data into database. Every variable of structure User must be
 * NULL or must contain some information about user.
 * @param User - structure that has data about user (nickname, password, email, age, fullname, phone_number, user_photo,
 * options). Nickname and password can't be NULL.
 * @return result of function 'check_valid_data_for_sign_up' if it doesn't 'success'
 * @return 'nickname_and_password_can_not_be_null' if nickname or password is NULL
 * @return 'can_not_open_db' if connection to database was lost
 * @return 'can_not_add_to_database' if request to add new use to database was failed
 * @return 'successfully_added_to_db' if new user was successfully added to database
 */

int add_user_to_db(t_user *User) {
    int result;
    sqlite3 *db;
    char *error = NULL;
    char *request = NULL;
    int test_in_db;

    // -------------------check if new user has valid nickname, email, phone number-------------------
    test_in_db = check_valid_data_for_sign_up(User);
    if (test_in_db != success)
        return test_in_db;
    // ----------------------------check if nickname and password not NULL-----------------------------
    if (!User->nickname || !User->password)
        return nickname_and_password_can_not_be_null;
    // -----------------------------------making request-----------------------------------------------
    request = (char *)malloc(sizeof(char) * get_len_of_request(User));
    request = strcpy(request, "INSERT INTO Users (nickname, password, email, age, fullname, phone_number"
                                  ", user_photo, options) VALUES ('");
    request = strcat(request, User->nickname);
    request = strcat(request, "', '");
    request = strcat(request, User->password);
    request = strcat(request, "', ");

    concatenate_with_request(&request, User->email);
    concatenate_with_request(&request, User->age);
    concatenate_with_request(&request, User->fullname);
    concatenate_with_request(&request, User->ph_number);
    concatenate_with_request(&request, User->user_photo);
    concatenate_with_request(&request, User->option);
    // ----------------------------adding to the database---------------------------------------------
    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK) {
        mx_strdel(&request);
        return can_not_open_db;
    }

    result = sqlite3_exec(db, request, 0, 0, &error);
    if (result != SQLITE_OK) {
        sqlite3_free(error);
        sqlite3_close(db);
        mx_strdel(&request);
        return can_not_add_to_database;
    }
    sqlite3_close(db);
    // ------------------------------------------------------------------------------------------------

    add_id_to_struct_User(User);

    if (request)
        free(request);

    return successfully_added_to_db;
}
