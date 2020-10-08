#include "server.h"

static int callback(void *my_arg, int argc, char **argv, char **column) {
    t_user *temp = (t_user *)my_arg;
    temp->id = strdup(argv[0]);
    return 0;
}

static char *make_request(char *wrapper,char *filling) {
    char *request = NULL;
    request = (char *)malloc(sizeof(char) * (strlen(wrapper) + strlen(filling) + 3));
    request = strcpy(request, wrapper);
    request = strcat(request, filling);
    request = strcat(request, "';");
    return request;
}

void add_id_to_struct_User(t_user *User) {
    sqlite3 *database;
    char *request;
    request = make_request("SELECT id FROM Users WHERE nickname='", User->nickname);
    sqlite3_open("chat_database.db", &database);
    sqlite3_exec(database, request, callback, User, 0);
    sqlite3_close(database);
    free(request);
}
