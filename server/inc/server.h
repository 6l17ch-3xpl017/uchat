#ifndef UCHAT_TEST_SERVER_H
#define UCHAT_TEST_SERVER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include "libmx.h"
#include "jansson.h"
#include "jansson_config.h"
#include "header_db_dev.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/stat.h>
#include <syslog.h>
#include <time.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "net_skeleton.h"
//#include "openssl/inc/openssl/bio.h"

#define check(expr) if (!(expr)) { perror(#expr); kill(0, SIGTERM); }

#define NO_UPDATES 1
#define UPDATED 2

enum status {
    unknown_error = -10,
    ok_check_route = 5,
    log_out = 0
};

typedef struct test {
    char *test;
    struct test *next;
}   t_test;

// router
int check_route(char *str, struct ns_connection *socket);
t_user *user_sign_in(json_t *income_json, struct ns_connection *socket);
t_user *user_sign_up(json_t *income_json, struct ns_connection *socket);
void send_status(t_user *User, t_chat *Chat, struct ns_connection *conn, int status, char *func);

//messages
void create_new_message(json_t *income_json, struct ns_connection *socket);
char *message_pack_send(t_message *Message, int status);

//chats
void create_new_empty_chat(json_t *income_json, struct ns_connection *socket);
char *new_chat_pack_send(t_chat *Chat, int status);
void open_selected_chat(json_t *income_json, struct ns_connection *socket);
void check_for_updates(json_t *income_json, struct ns_connection *socket);
void free_chat_struct(t_chat *Chat);

#endif
