#include "server.h"

static int callback(void *my_arg, int argc, char **argv, char **column) {
    t_chat *temp = (t_chat *)my_arg;
    temp->chat_id = strdup(argv[0]);
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

void add_id_to_struct_Chat(t_chat *Chat) {
    sqlite3 *database;
    char *request;
    request = make_request("SELECT chat_id FROM Chats WHERE chat_name='", Chat->chat_name);
    sqlite3_open("chat_database.db", &database);
    sqlite3_exec(database, request, callback, Chat, 0);
    sqlite3_close(database);
    free(request);
}
