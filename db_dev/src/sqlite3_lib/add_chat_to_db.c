#include "header_db_dev.h"

static int get_len_of_item(char *item) {
    if (item)
        return (int)strlen(item) + 4;
    else
        return 6;
}

static int get_len_of_request(t_chat *Chat) {
    int result = 70;
    result += get_len_of_item(Chat->chat_name);
    result += get_len_of_item(Chat->admin_id);
    result += get_len_of_item(Chat->chat_photo);
    result += get_len_of_item(Chat->option);
    return result;
}

static void concatenate_with_request(char **request, char *info) {
    static int counter = 0;
    if (counter == 3) {
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
 * @author Ilay Marchenko
 * @brief Function add chat into table 'Chats' in database. Every variable of structure User must be NULL or must
 *        contain some information about user.
 * @param Chat - structure that has data about chat (chat_name, admin_id, chat_photo, options). Chat_name and admin_id
 *        can't be NULL.
 */

void add_chat_to_db(t_chat *Chat) {
    int result;
    sqlite3 *db;
    char *error = NULL;
    char *request = NULL;

    request = (char *)malloc(sizeof(char) * get_len_of_request(Chat));

    if (!Chat->chat_name || !Chat->admin_id) {
        printf("Chat->chat_name or Chat->admin_id can't be NULL!\n");
        return;
    }

    request = strcpy(request, "INSERT INTO Chats (chat_name, admin_id, chat_photo, options) VALUES (");
    concatenate_with_request(&request, Chat->chat_name);
    concatenate_with_request(&request, Chat->admin_id);
    concatenate_with_request(&request, Chat->chat_photo);
    concatenate_with_request(&request, Chat->option);

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

    add_id_to_struct_Chat(Chat);

    if (request)
        free(request);
}
