#include "header_db_dev.h"

static int callback(void *my_arg, int argc, char **argv, char **column) {
    t_message *temp = (t_message *)my_arg;
    temp->message_id = strdup(argv[0]);
    return 0;
}

static char *make_request_for_message(char *wrapper,char *key1, char *key2, char *message_content, char *time) {
    char *request = NULL;
    request = (char *)malloc(sizeof(char) * (strlen(wrapper) + strlen(key1) + strlen(key2) +strlen(message_content)
            + strlen(time) + 15 + 23 + 12 + 3));
    request = strcpy(request, wrapper);
    request = strcat(request, key1);
    request = strcat(request, "' AND chat_id='");
    request = strcat(request, key2);
    request = strcat(request, "' AND message_content='");
    request = strcat(request, message_content);
    request = strcat(request, "' AND time='");
    request = strcat(request, time);
    request = strcat(request, "';");
    return request;
}

void add_id_to_struct_Message(t_message *Message) {
    sqlite3 *database;
    char *request;
    char *time = mx_itoa(Message->time);
    request = make_request_for_message("SELECT message_id FROM Messages WHERE message_owner_id='",
            Message->message_owner_id, Message->chat_id, Message->message_content, time);
    sqlite3_open("chat_database.db", &database);
    sqlite3_exec(database, request, callback, Message, 0);
    puts("msg id(add_id_to_struct_Message): ");
    puts(Message->message_id);
    sqlite3_close(database);
    mx_strdel(&time);
    free(request);
}

