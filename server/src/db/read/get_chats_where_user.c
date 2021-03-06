#include "header_db_dev.h"

static void free_and_dup(char **a, char *b) {
    if (*a)
        free(*a);
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

int get_chats_where_user(t_user *User) {
    sqlite3 *db;
    char *request = NULL;
    int result;

    connect_to_db

// temp structure to keep all id numbers
    t_chats_id *chats_id = (t_chats_id *) malloc(sizeof(t_chats_id));
    chats_id->number_of_chats = 0;

// first request to get all user's chat id numbers
    make_sql_request(&request, "SELECT chat_id FROM Chat_User WHERE user_id = %s ;", User->id);
    result = sqlite3_exec(db, request, callback_for_id, chats_id, 0);
    if (result != SQLITE_OK) {
        mx_strdel(&request);
        free(chats_id);
        return request_failed;
    }
    mx_strdel(&request);

// block to make linked list of data about user's chats
    User->number_of_chats = chats_id->number_of_chats;
    User->chats = (t_chat *) malloc(sizeof(t_chat));
    t_chat *temp_chat = User->chats;
    for (int i = 0; i < chats_id->number_of_chats; i++) {
        make_sql_request(&request, "SELECT * FROM Chats WHERE chat_id = %s ;", chats_id->chat_id[i]);
        init_chat_struct(temp_chat);
        sqlite3_exec(db, request, callback_for_data, temp_chat, 0);
        if ((i + 1) < chats_id->number_of_chats)
            temp_chat->next = (t_chat *)malloc(sizeof(t_chat));
        else
            temp_chat->next = NULL;
        get_users_list_for_chat(temp_chat);
        temp_chat = temp_chat->next;
        mx_strdel(&request);
    }

// block to close db and clean memory
    for (int i = 0; i < chats_id->number_of_chats; ++i)
        mx_strdel(&chats_id->chat_id[i]);

    if (chats_id->number_of_chats != 0)
        free(chats_id->chat_id);

    free(chats_id);
    sqlite3_close(db);
    return success;
}
