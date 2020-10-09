#include "server.h"

static void free_and_dup(char **a, char *b) {
    if (b)
        *a = strdup(b);
    else
        *a = NULL;
}

static int callback_for_data(void *my_arg, int argc, char **argv, char **columns) {
    t_chat *temp = (t_chat *)my_arg;
    free_and_dup(&temp->chat_id,               argv[0]);
    free_and_dup(&temp->chat_name,             argv[1]);
    free_and_dup(&temp->admin_id,              argv[2]);
    free_and_dup(&temp->chat_photo,            argv[3]);
    free_and_dup((char **)(&temp->option),     argv[4]);
    return 0;
}

static int callback_for_id(void *my_arg, int argc, char **argv, char **columns) {
    t_chats_id *temp = (t_chats_id *)my_arg;
    if (temp->number_of_chats == 0)
        temp->chat_id = (char **)malloc(sizeof(char *) * 1000);
    temp->chat_id[temp->number_of_chats] = strdup(argv[0]);
    temp->number_of_chats++;
    return 0;
}


static void make_request(char **request, char *id, char *request_content) {
    *request = mx_strnew((int)strlen(request_content) + (int)strlen(id));
    *request = strcpy(*request, request_content);
    *request = strcat(*request, id);
    *request = strcat(*request, "\";");
}

void get_chats_where_user(t_user *User) {
    sqlite3 *database;
    char *request = NULL;
    char *error;
    int result;

// temp structure to keep all id numbers
    t_chats_id *chats_id = (t_chats_id *) malloc(sizeof(t_chats_id));
    chats_id->number_of_chats = 0;

// first request to get all user's chat id numbers
    make_request(&request, User->id, "SELECT chat_id FROM Chat_User WHERE user_id = \"");
    sqlite3_open("chat_database.db", &database);
    result = sqlite3_exec(database, request, callback_for_id, chats_id, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }
    mx_strdel(&request);

// block to make linked list of data about user's chats
    User->number_of_chats = chats_id->number_of_chats;
    User->chats = (t_chat *) malloc(sizeof(t_chat));
    t_chat *temp_chat = User->chats;
    for (int i = 0; i < chats_id->number_of_chats; i++) {
        make_request(&request, chats_id->chat_id[i], "SELECT * FROM Chats WHERE chat_id = \"");
        sqlite3_exec(database, request, callback_for_data, temp_chat, &error);
        temp_chat->next = (t_chat *) malloc(sizeof(t_chat));
        temp_chat = temp_chat->next;
        mx_strdel(&request);
    }

// block to close db and clean memory
    for (int i = 0; i < chats_id->number_of_chats; ++i)
        mx_strdel(&chats_id->chat_id[i]);

    if (chats_id->number_of_chats != 0)
        free(chats_id->chat_id);

    free(chats_id);
    sqlite3_close(database);
}
