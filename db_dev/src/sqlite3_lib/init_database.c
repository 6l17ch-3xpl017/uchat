//
// Created by Illia Marchenko on 9/27/20.
//

#include "header_db_dev.h"

/**
 * @author Illia Marchenko
 * @brief Function creates database if database wasn't created before and creates all tables if they weren't created yet.
 * @name 'init_database' - because we should call it everytime before chat turning on to be sure that with database everything fine.
 */

void init_database() {
    sqlite3 *db;
    char *error = NULL;
    int result;

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK) {
        printf("Can't open database\n");
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
                              "\"chat_name\"\tTEXT NOT NULL UNIQUE,\n"
                              "\"admin_id\"\tINTEGER NOT NULL,\n"
                              "\"chat_photo\"\tTEXT,\n"
                              "\"options\"\tTEXT,\n"
                              "PRIMARY KEY(\"chat_id\" AUTOINCREMENT)\n"
                              "FOREIGN KEY(\"admin_id\") REFERENCES Users (\"id\")"
                              ");", 0, 0, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }
    // -------------------------------------------------------------------------------------------

    // -----------------------------=-Block to create Chat-User table-=---------------------------
    result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS \"Chat_User\" (\n"
                              "\"chat_id\"\tINTEGER NOT NULL,\n"
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
                              "\"message_owner_id\"\tINTEGER NOT NULL,\n"
                              "\"chat_id\"\tINTEGER NOT NULL,\n"
                              "\"message_content\"\tTEXT NOT NULL,\n"
                              "\"time\"\tINTEGER,\n"
                              "\"changed\"\tINTEGER,\n"
                              "\"options\"\tTEXT,\n"
                              "PRIMARY KEY(\"message_id\" AUTOINCREMENT)\n"
                              "FOREIGN KEY(\"message_owner_id\") REFERENCES Users (\"id\")\n"
                              "FOREIGN KEY(\"chat_id\") REFERENCES Chats (\"chat_id\")"
                              ");", 0, 0, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }
    // -------------------------------------------------------------------------------------------

    sqlite3_close(db);
}
