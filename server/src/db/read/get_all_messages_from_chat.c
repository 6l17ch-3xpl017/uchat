#include "header_db_dev.h"

static int callback_for_id(void *my_arg, int argc, char **argv, char **columns) {
    t_messages_id *temp = (t_messages_id *)my_arg;
    if (temp->number_of_messages == 0)
        temp->message_id = (char **)malloc(sizeof(char *));
    else
        temp->message_id = realloc(temp->message_id, (temp->number_of_messages + 1) * sizeof(char *));
    temp->message_id[temp->number_of_messages] = strdup(argv[0]);
    temp->number_of_messages++;
    return 0;
}

static void free_and_dup(char **a, char *b) {
    if (*a)
        free(*a);
    if (b)
        *a = strdup(b);
    else
        *a = NULL;
}

static int callback_for_data(void *my_arg, int argc, char **argv, char **columns) {
    t_message *message = (t_message *)my_arg;
    free_and_dup(&message->message_id,            argv[0]);
    free_and_dup(&message->message_owner_id,      argv[1]);
    free_and_dup(&message->message_owner_name,      argv[2]);
    free_and_dup(&message->chat_id,               argv[3]);
    free_and_dup(&message->message_content,       argv[4]);
    free_and_dup(&message->type,                  argv[8]);
    free_and_dup((char **)(&message->option),     argv[9]);
    message->deleted = atoi(argv[7]);
    free_and_dup(&message->time,                  argv[8]);
    message->changed = atoi(argv[6]);
    return 0;
}

int get_all_messages_from_db(t_chat *Chat) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    if (!Chat)
        return 0;

    connect_to_db

    t_messages_id *messages_id = (t_messages_id *) malloc(sizeof(t_messages_id));
    messages_id->number_of_messages = 0;

// first request to get all messages id numbers
    make_sql_request(&request, "SELECT message_id FROM Messages WHERE chat_id=%s ORDER BY time;", Chat->chat_id);
    result = sqlite3_exec(db, request, callback_for_id, messages_id, 0);
    mx_strdel(&request);

    if (result != SQLITE_OK) {
        sqlite3_close(db);
        return request_failed;
    }

// block to make linked list of data about chat's messages
    Chat->number_of_messages = messages_id->number_of_messages;
    Chat->next_message = (t_message *)malloc(sizeof(t_message));
    t_message *current_message = Chat->next_message;
    for (int i = 0; i < messages_id->number_of_messages; i++) {
        make_sql_request(&request, "SELECT * FROM Messages WHERE message_id=%s;", messages_id->message_id[i]);
        init_message_struct(current_message);
        sqlite3_exec(db, request, callback_for_data, current_message, 0);
        if ((i + 1) < messages_id->number_of_messages)
            current_message->next = (t_message *)malloc(sizeof(t_message));
        else
            current_message->next = NULL;
        current_message = current_message->next;
        mx_strdel(&request);
    }

    // block to close db and clean memory
    for (int i = 0; i < messages_id->number_of_messages; ++i)
        mx_strdel(&messages_id->message_id[i]);

    if (messages_id->number_of_messages != 0)
        free(messages_id->message_id);

    free(messages_id);
    sqlite3_close(db);
    return success;
}
