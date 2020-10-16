#include "header_db_dev.h"

static void copy_to_structure(char **str1, char *str2) {
    if (str2)
        *str1 = strdup(str2);
}

static void init_message_structure(t_message **structure) {
    *structure = (t_message *)malloc(sizeof(t_message));
    (*structure)->message_id = NULL;
    (*structure)->message_content = NULL;
    (*structure)->message_owner_id = NULL;
    (*structure)->chat_id = NULL;
    (*structure)->time = 0;
    (*structure)->next = NULL;
    (*structure)->option = NULL;
    (*structure)->changed = 0;
}

static int callback_for_id(void *my_arg, int argc, char **argv, char **columns) {
//    t_messages_id *temp = (t_messages_id *)my_arg;
//    if (temp->number_of_messages == 0)
//        temp->message_id = (char **)malloc(sizeof(char *));
//    else
//        temp->message_id = realloc(temp->message_id, (temp->number_of_messages + 1) * sizeof(char *));
//    temp->message_id[temp->number_of_messages] = strdup(argv[0]);
//    temp->number_of_messages++;

    static t_message *temp;
    static int counter = 0;
    if (counter == 0)
        temp = (t_message *)my_arg;
    else
        init_message_structure(&temp);
    copy_to_structure(&temp->message_id,       argv[0]);
    copy_to_structure(&temp->message_owner_id, argv[1]);
    copy_to_structure(&temp->chat_id,          argv[2]);
    copy_to_structure(&temp->message_content,  argv[3]);
    copy_to_structure(&temp->option,           argv[6]);
    temp->time = (long)argv[4];
    temp->changed = atoi(argv[5]);
    temp = temp->next;
    counter++;
    return 0;
}

static void make_request(char **request, char *id, char *request_content) {
    *request = mx_strnew((int)strlen(request_content) + (int)strlen(id) + 30);
    *request = strcpy(*request, request_content);
    *request = strcat(*request, id);
    *request = strcat(*request, "'ORDER BY time;");
}

int get_all_messages_from_struct(t_chat *Chat) {
    sqlite3 *database;
    char *request = NULL;
    int result;

// first request to get all messages id numbers
    make_request(&request, Chat->chat_id, "SELECT * FROM Messages WHERE chat_id='");
    result = sqlite3_open("chat_database.db", &database);
    if (result != SQLITE_OK) {
        mx_strdel(&request);
        return can_not_open_db;
    }
    init_message_structure(&Chat->next_message);
    result = sqlite3_exec(database, request, callback_for_id, Chat->next_message, 0);
    if (result != SQLITE_OK) {
        mx_strdel(&request);
        return request_failed;
    }
    sqlite3_close(database);
    return 0;
}
