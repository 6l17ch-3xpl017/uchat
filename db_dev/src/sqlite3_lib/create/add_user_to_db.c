#include "header_db_dev.h"

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
    char *request;
    int test_in_db;

    connect_to_db

    // -------------------check if new user has valid nickname, email, phone number-------------------
    test_in_db = check_valid_data_for_sign_up(User);
    if (test_in_db != success)
        return test_in_db;
    // ----------------------------check if nickname and password not NULL-----------------------------
    if (!User->nickname || !User->password)
        return nickname_and_password_can_not_be_null;
    // -----------------------------------making request-----------------------------------------------
    request = make_sql_request(&request, "INSERT INTO Users (nickname, password, email, age, fullname, "
                                         "phone_number, user_photo, options) VALUES (%s, %s, %s, %s, %s, %s, %s, %s);",
                                         User->nickname, User->password, User->email, User->age, User->fullname,
                                         User->ph_number, User->user_photo, (char *)User->option);
    // ----------------------------adding to the database---------------------------------------------
    result = sqlite3_exec(db, request, 0, 0, 0);
    if (result != SQLITE_OK) {
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
