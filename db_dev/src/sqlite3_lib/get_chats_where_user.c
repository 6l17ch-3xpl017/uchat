#include "header_db_dev.h"

static int callback(void *my_arg, int argc, char **argv, char **columns) {
    t_user *temp = (t_user *)my_arg;
    if (temp->number_of_chats == 0)
        temp->chats = (char **)malloc(sizeof(char *) * 100);
    temp->chats[temp->number_of_chats] = strdup(argv[0]);
    temp->number_of_chats++;
    return 0;
}

static void make_request(char **request, char *id) {
    *request = (char *)malloc(sizeof(char) * (46 + strlen(id)));
    *request = strcpy(*request, "SELECT chat_id FROM Chat_User WHERE user_id = ");
    *request = strcat(*request, id);
    *request = strcat(*request, ";");
}

void get_chats_where_user(t_user *User) {
    sqlite3 *database;
    char *request = NULL;
    char *error;
    int result;

    if (User->chats)
        mx_del_strarr(&User->chats);

    make_request(&request, User->id);
    User->number_of_chats = 0;
    sqlite3_open("chat_database.db", &database);
    result = sqlite3_exec(database, request, callback, User, &error);
    if (result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error);
        sqlite3_free(error);
    }
    mx_strdel(&request);
    sqlite3_close(database);
}
