#include "header_db_dev.h"

static void free_and_dup(char **a, char *b) {
    if (*a)
        free(*a);
    if (b)
        *a = strdup(b);
    else
        *a = NULL;
}

static int callback_data(void *my_arg, int argc, char **argv, char **columns) { // TODO Finish this func !!!!
    t_user *current = (t_user *)my_arg;
    free_and_dup(&current->id,                    argv[0]);
    free_and_dup(&current->nickname,              argv[1]);
    free_and_dup(&current->password,              argv[2]);
    free_and_dup(&current->email,                 argv[3]);
    free_and_dup(&current->age,                   argv[4]);
    free_and_dup(&current->fullname,              argv[5]);
    free_and_dup(&current->ph_number,             argv[6]);
    free_and_dup(&current->user_photo,            argv[7]);
    free_and_dup((char **)(&current->option),     argv[8]);
    return 0;
}

int callback_id(void *my_arg, int argc, char **argv, char **columns) {
    t_user_id *user_id = (t_user_id *)my_arg;
    if (user_id->number_of_users == 0)
        user_id->user_id = (char **)malloc(sizeof(char *) * 1000);
    user_id->user_id[user_id->number_of_users] = strdup(argv[0]);
    user_id->number_of_users++;
    return 0;
}

int get_users_list_for_chat(t_chat *Chat) {
    int result;
    sqlite3 *db;
    char *request;
    t_user_id *user_id = (t_user_id *)malloc(sizeof(t_user_id));
    user_id->number_of_users = 0;

    if (!Chat || !Chat->chat_id) {
        return chat_does_not_exist;
    }

    result = sqlite3_open("chat_database.db", &db);
    if (result != SQLITE_OK)
        return can_not_open_db;

    make_sql_request(&request, "SELECT user_id FROM Chat_User WHERE chat_id = %s ;", Chat->chat_id);
    result = sqlite3_exec(db, request, callback_id, user_id, 0);
    if (result != SQLITE_OK) {
        mx_strdel(&request);
        sqlite3_close(db);
        return request_failed;
    }
    mx_strdel(&request);

    Chat->number_of_users = user_id->number_of_users;
    Chat->user_in_chat = (t_user *) malloc(sizeof(t_user));
    t_user *current_user = Chat->user_in_chat;
    for (int i = 0; i < user_id->number_of_users; i++) {
        make_sql_request(&request, "SELECT * FROM Users WHERE id = %s ;", user_id->user_id[i]);
        init_user_struct(current_user);
        sqlite3_exec(db, request, callback_data, current_user, 0);
        if ((i + 1) < user_id->number_of_users)
            current_user->next = (t_user *)malloc(sizeof(t_user));
        else
            current_user->next = NULL;
        current_user = current_user->next;
        mx_strdel(&request);
    }
    for (int i = 0; i < user_id->number_of_users; ++i)
        mx_strdel(&user_id->user_id[i]);

    if (user_id->number_of_users != 0)
        free(user_id->user_id);
    free(user_id);
    sqlite3_close(db);

    return success;
}
