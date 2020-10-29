#include "header_db_dev.h"

static void free_and_dup(char **a, char *b) {
    if (*a)
        free(*a);
    if (b)
        *a = strdup(b);
    else
        *a = NULL;
}

static int callback(void *my_arg, int argc, char **argv, char **columns) {
    t_user *buf = (t_user *)my_arg;
    free_and_dup(&buf->id,              argv[0]);
    free_and_dup(&buf->nickname,        argv[1]);
    free_and_dup(&buf->password,        argv[2]);
    free_and_dup(&buf->email,           argv[3]);
    free_and_dup(&buf->age,             argv[4]);
    free_and_dup(&buf->fullname,        argv[5]);
    free_and_dup(&buf->ph_number,       argv[6]);
    free_and_dup(&buf->user_photo,      argv[7]);
    free_and_dup((char **)&buf->option, argv[8]);
    return 0;
}

static char *make_request(char *wrapper,char *filling) {
    char *request = NULL;
    request = (char *)malloc(sizeof(char) * (38 + strlen(filling)));
    request = strcpy(request, wrapper);
    request = strcat(request, filling);
    request = strcat(request, "';");
    return request;
}

/**
 * @brief Function copy all data from database to structure 'User'. If in structure we have some data, this data
 *        will be refreshed.
 * @param User - pointer to structure in which function will copy data from database.
 */

int populate_User_struct(t_user *User) {
    sqlite3 *database;
    char *request = NULL;
    int temp_res;

    sqlite3_open("chat_database.db", &database);
    if (User->id)
        request = make_request("SELECT * FROM Users WHERE id='", User->id);
    else if (User->nickname)
        request = make_request("SELECT * FROM Users WHERE nickname='", User->nickname);
    else if (User->email)
        request = make_request("SELECT * FROM Users WHERE email='", User->email);

    sqlite3_exec(database, request, callback, User, 0);
    free(request);
    sqlite3_close(database);

    if (User->chats != NULL)
        mx_del_chat_list(User->chats, User->number_of_chats);

    if ((temp_res = get_chats_where_user(User)) != success)
        return temp_res;

    return success;
}

