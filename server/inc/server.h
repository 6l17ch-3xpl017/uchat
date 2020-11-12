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

enum status {
    unknown_error = -10,
    ok_check_route = 5,
    log_out = 0
};

// router
int check_route(char *str, struct ns_connection *socket);
t_user *user_sign_in(json_t *income_json, struct ns_connection *socket);
t_user *user_sign_up(json_t *income_json, struct ns_connection *socket);
void send_status(t_user *User, t_chat *Chat, struct ns_connection *conn, int status, char *func);
void create_new_message(json_t *income_json, struct ns_connection *socket);
char *message_pack_send(t_message *Message, int status);
void create_new_empty_chat(json_t *income_json, struct ns_connection *socket);
void open_selected_chat(json_t *income_json, struct ns_connection *socket);

#endif
