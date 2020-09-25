//
// Created by Illia Marchenko on 9/24/20.
//

#include "header_db_dev.h"

static void create_open_Users() {
    sqlite3 *db;
    char *error = NULL;
    int result;

    result = sqlite3_open("test.db", &db);
    if (result != SQLITE_OK) {
        printf("can't open\n");
        exit(1);
    }

    result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS\"Users\" (\n"
                              "\"id\"\tINTEGER NOT NULL UNIQUE,\n"
                              "\"nickname\"\tTEXT NOT NULL UNIQUE,\n"
                              "\"password\"\tTEXT NOT NULL,\n"
                              "\"email\"\tTEXT NOT NULL UNIQUE,\n"
                              "\"age\"\tINTEGER NOT NULL,\n"
                              "\"full_name\"\tTEXT NOT NULL,\n"
                              "\"phone_number\"\tTEXT,\n"
                              "\"user_photo\"\tTEXT,\n"
                              "\"options\"\tTEXT,\n"
                              "PRIMARY KEY(\"id\" AUTOINCREMENT)\n"
                              ");", 0, 0, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }
    else {
        printf("Table created successfully\n");
    }
    sqlite3_close(db);
}

static void add_to_table(char *nickname, char *password, char *email, int age, char *fullname, char *phone_number,
                         char *user_photo, void *option) {
    sqlite3 *db;
    char *error = NULL;
    int result;
    char *request;
    char *option_str = NULL;

    result = sqlite3_open("test.db", &db);
    if (result != SQLITE_OK) {
        printf("Can't open database\n");
        exit(1);
    }

    if (!option) {
        option_str = strdup("NULL");
    }
    else {
        option_str = (char *)option;
    }

    asprintf(&request, "INSERT INTO Users (nickname, password, email, age, fullname, phone_number, user_photo, option)"
                       "VALUES ('%s', '%s', '%s', '%d', '%s', '%s', '%s', '%s');", nickname, password, email, age,
                       fullname, phone_number, user_photo, option_str);

    printf("%s\n", request);

    sqlite3_close(db);
    free(request);
}

int main() {
    add_to_table("imarchenko", "qwerty", "ilya.marchenko02@gmail.com", 18, "Illia Marchenko", "+380 63 599 64 22",
                 "/photos/imarchenko", NULL);
    system("leaks -q UCHAT");
    return 0;
}
