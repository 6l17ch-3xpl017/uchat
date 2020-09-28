//
// Created by Illia Marchenko on 9/28/20.
//

#include "../inc/header_db_dev.h"

void add_chat_to_db(t_chat *Chat) {
    int result;
    sqlite3 *db;
    char *error = NULL;
    char *request = NULL;

    asprintf(&request, "INSERT INTO Chats (chat_name, admin_id, chat_photo, options)\n"
             "VALUES ('%s', '%s', ", Chat->chat_name, Chat->admin_id);

    if (Chat->chat_photo) {
        request = realloc(request, strlen(request) + strlen(Chat->chat_photo) + strlen("'', "));
        request = strcat(request, "'");
        request = strcat(request, Chat->chat_photo);
        request = strcat(request, "', ");
    }
    else {
        request = realloc(request, strlen(request) + strlen("NULL, "));
        request = strcat(request, "NULL, ");
    }

    if (Chat->option) {
        request = realloc(request, strlen(request) + strlen(Chat->option) + strlen("'');"));
        request = strcat(request, "'");
        request = strcat(request, Chat->option);
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
