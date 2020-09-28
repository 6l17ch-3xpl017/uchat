//
// Created by Illia Marchenko on 9/24/20.
//

#include "header_db_dev.h"

/**
 * @author Illia Marchenko
 * @brief Function creates database if database wasn't created before and creates all tables if they weren't created yet.
 * @name 'init_database' - because we should call it everytime before chat turning on to be sure that with database everything fine.
 *
 */

void init_database() {
    sqlite3 *db;
    char *error = NULL;
    int result;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK) {
        printf("Can't open\n");
        exit(1);
    }

    // -----------------------------=-Block to create Users table-=-------------------------------
    result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS\"Users\" (\n"
                              "\"id\"\tINTEGER NOT NULL UNIQUE,\n"
                              "\"nickname\"\tTEXT NOT NULL UNIQUE,\n"
                              "\"password\"\tTEXT NOT NULL,\n"
                              "\"email\"\tTEXT UNIQUE,\n"
                              "\"age\"\tINTEGER,\n"
                              "\"fullname\"\tTEXT,\n"
                              "\"phone_number\"\tTEXT,\n"
                              "\"user_photo\"\tTEXT,\n"
                              "\"options\"\tTEXT,\n"
                              "PRIMARY KEY(\"id\" AUTOINCREMENT)\n"
                              ");", 0, 0, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }
    // -------------------------------------------------------------------------------------------

    // -----------------------------=-Block to create Chats table-=-------------------------------
    result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS \"Chats\" (\n"
                              "\"chat_id\"\tINTEGER NOT NULL UNIQUE,\n"
                              "\"chat_name\"\tTEXT,\n"
                              "\"admin_id\"\tINTEGER NOT NULL,\n"
                              "\"chat_photo\"\tTEXT,\n"
                              "\"options\"\tTEXT,\n"
                              "PRIMARY KEY(\"chat_id\" AUTOINCREMENT)\n"
                              ");", 0, 0, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }
    // -------------------------------------------------------------------------------------------

    // -----------------------------=-Block to create Chat-User table-=---------------------------
    result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS \"Chat_User\" (\n"
                              "\"char_id\"\tINTEGER NOT NULL,\n"
                              "\"user_id\"\tINTEGER NOT NULL,\n"
                              "\"options\"\tTEXT\n"
                              ");", 0, 0, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }
    // -------------------------------------------------------------------------------------------

    // -----------------------------=-Block to create Messages table-=----------------------------
    result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS \"Messages\" (\n"
                              "\"message_id\"\tINTEGER NOT NULL UNIQUE,\n"
                              "\"message_owner\"\tTEXT NOT NULL,\n"
                              "\"chat_id\"\tINTEGER NOT NULL,\n"
                              "\"message_content\"\tTEXT NOT NULL,\n"
                              "\"time\"\tINTEGER,\n"
                              "\"changed\"\tINTEGER,\n"
                              "\"options\"\tTEXT,\n"
                              "PRIMARY KEY(\"message_id\" AUTOINCREMENT)\n"
                              ");", 0, 0, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }
    // -------------------------------------------------------------------------------------------

    sqlite3_close(db);
}

/**
 * POKA CHTO HYEVO RABOTAET !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

void add_to_table_Users(char *nickname, char *password, char *email, int age, char *fullname, char *phone_number,
                         char *user_photo, void *option) {
    sqlite3 *db;
    char *error = NULL;
    int result;
    char *request;

    char *option_str = NULL;
    char *age_str = NULL;


    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK) {
        printf("Can't open database\n");
        exit(1);
    }

    // -----------------------------Block to check null values-----------------------------
    if (!nickname || !password) {
        printf("nickname and password cant be null!\n");
        return;
    }

    if (!email)
        email = strdup("NULL");

    if (!age)
        age_str = strdup("NULL");
    else {
        age_str = mx_itoa(age);
    }

    if (!fullname)
        fullname = strdup("NULL");

    if (!phone_number)
        phone_number = strdup("NULL");

    if (!user_photo)
        user_photo = strdup("NULL");

    if (!option)
        option_str = strdup("NULL");
    else {
        option_str = (char *)option;
    }
    // -------------------------------------------------------------------------------------

    asprintf(&request, "INSERT INTO Users (nickname, password, email, age, fullname, phone_number, user_photo, options)"
                       "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');", nickname, password, email, age_str,
                       fullname, phone_number, user_photo, option_str);

    printf("%s\n", request);


    result = sqlite3_exec(db, request, 0, 0, &error);

    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }

    sqlite3_close(db);

    if (strcmp(email, "NULL") == 0)
        free(email);

//    if (age_str)          //ToDo: fix bug with tis fucking 1 leak and 'pointer being freed was not allocated'
//        free(age_str);

    if (strcmp(fullname, "NULL") == 0)
        free(fullname);

    if (strcmp(phone_number, "NULL") == 0)
        free(phone_number);

    if (strcmp(user_photo, "NULL") == 0)
        free(user_photo);

    if (option_str)
        free(option_str);

    free(request);
}

int main() {
    init_database();
    bool a = if_user_in_db("imarch");
    if (a)
        printf("user in db\n");
    else
        printf("user not in db\n");
    system("leaks -q UCHAT");
    return 0;
}
