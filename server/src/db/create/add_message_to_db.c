#include "header_db_dev.h"

static int get_len_of_item(char *item) {
    if (item)
        return (int)strlen(item) + 4;
    else
        return 6;
}

static int get_len_of_request(t_message *Message) {
    int result = 132 + 6 * 4;
    result += get_len_of_item(Message->message_owner_id);
    result += get_len_of_item(Message->chat_id);
    result += get_len_of_item(Message->message_content);
    result += 12; //time
    result += 1; //changed
    result += get_len_of_item(Message->option);
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
 * @brief Function takes structure with data and paste this data into database. Every variable of structure Message must be
 * NULL or must contain some information about message.
 * @param Message - structure that has data about the message (message_id, message_owner_id, chat_id, message_content,
 * time, changed, options). message_id, message_owner_id and chat_id can't be NULL.
    //TODO Add documentation
 * @return 'can_not_open_db' if connection to database was lost
 * @return 'can_not_add_to_database' if request to add new use to database was failed
 * @return 'successfully_added_to_db' if new user was successfully added to database
 */

int add_message_to_db(t_message *Message) {
    int result;
    sqlite3 *db;
    char *request = NULL;

    // ----------------------------check if nickname and password not NULL-----------------------------
    if (!Message->message_content)
        return message_cannot_be_empty;
    // -----------------------------------making request-----------------------------------------------
    request = (char *)malloc(sizeof(char) * get_len_of_request(Message));
    request = strcpy(request, "INSERT INTO Messages (message_owner_id, chat_id, message_content, time, "
                              "changed, options) VALUES (");

    char *temp = NULL;
    concatenate_with_request(&request, Message->message_owner_id);
    concatenate_with_request(&request, Message->chat_id);
    concatenate_with_request(&request, Message->message_content);
    temp = mx_itoa(Message->time);
    concatenate_with_request(&request, temp);
    mx_strdel(&temp);
    char *temp1 = NULL;
    temp1 = mx_itoa(Message->changed);
    concatenate_with_request(&request, temp1);
    mx_strdel(&temp1);
    concatenate_with_request(&request, Message->option);
    // ----------------------------adding to the database---------------------------------------------
    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK) {
        mx_strdel(&request);
        return can_not_open_db;
    }

    result = sqlite3_exec(db, request, 0, 0, 0);
    if (result != SQLITE_OK) {
        sqlite3_close(db);
        mx_strdel(&request);
        return can_not_add_to_database;
    }
    sqlite3_close(db);
    // ------------------------------------------------------------------------------------------------

    add_id_to_struct_Message(Message);

    if (request)
        free(request);

    return successfully_added_to_db;
}
