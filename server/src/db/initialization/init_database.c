#include "header_db_dev.h"

/**
 * @author Illia Marchenko
 * @brief Function creates database if database wasn't created before and creates all tables if they weren't created yet.
 * @name 'init_database' - because we should call it everytime before chat turning on to be sure that with database everything fine.
 */

int init_database() {
    sqlite3 *db;
    int result;

    connect_to_db

    // -----------------------------=-Block to create Users table-=-------------------------------
    result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS\"Users\" (\n"
                              "\"id\"\tINTEGER NOT NULL UNIQUE,\n"
                              "\"nickname\"\tTEXT NOT NULL UNIQUE,\n"
                              "\"password\"\tTEXT NOT NULL,\n"
                              "\"email\"\tTEXT UNIQUE,\n"
                              "\"age\"\tINTEGER,\n"
                              "\"fullname\"\tTEXT,\n"
                              "\"phone_number\"\tTEXT UNIQUE,\n"
                              "\"user_photo\"\tTEXT,\n"
                              "\"country\"\tTEXT,\n"
                              "\"options\"\tTEXT,\n"
                              "PRIMARY KEY(\"id\" AUTOINCREMENT)\n"
                              ");", 0, 0, 0);
    if (result != SQLITE_OK) {
        sqlite3_close(db);
        return can_not_create_users_table;
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
                              ");", 0, 0,0);
    if (result != SQLITE_OK) {
        sqlite3_close(db);
        return can_not_create_chats_table;
    }
    // -------------------------------------------------------------------------------------------

    // -----------------------------=-Block to create Chat-User table-=---------------------------
    result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS \"Chat_User\" (\n"
                              "\"chat_id\"\tINTEGER NOT NULL,\n"
                              "\"user_id\"\tINTEGER NOT NULL,\n"
                              "\"options\"\tTEXT\n"
                              ");", 0, 0, 0);
    if (result != SQLITE_OK) {
        sqlite3_close(db);
        return can_not_create_chat_user_table;
    }
    // -------------------------------------------------------------------------------------------

    // -----------------------------=-Block to create Messages table-=----------------------------
    result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS \"Messages\" (\n"
                              "\"message_id\"\tINTEGER NOT NULL UNIQUE,\n"
                              "\"message_owner_id\"\tINTEGER NOT NULL,\n"
                              "\"message_owner_name\"\tTEXT NOT NULL,\n"
                              "\"chat_id\"\tINTEGER NOT NULL,\n"
                              "\"message_content\"\tTEXT NOT NULL,\n"
                              "\"time\"\tTEXT,\n"
                              "\"changed\"\tINTEGER,\n"
                              "\"deleted\"\tINTEGER,\n"
                              "\"type\"\tTEXT,\n"
                              "\"options\"\tTEXT,\n"
                              "PRIMARY KEY(\"message_id\" AUTOINCREMENT)\n"
                              ");", 0, 0, 0);
    if (result != SQLITE_OK) {
        sqlite3_close(db);
        return can_not_create_messages_table;
    }
    // -------------------------------------------------------------------------------------------

    sqlite3_close(db);
    return database_was_connected;
}
