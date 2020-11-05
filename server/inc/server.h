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
//#include "openssl/inc/openssl/bio.h"

#define check(expr) if (!(expr)) { perror(#expr); kill(0, SIGTERM); }

enum status {
    unknown_error = -10,
    ok_check_route = 5
};

typedef struct s_thread_sockuser {
    int socket;
    char *user;
} t_thread_sockuser;

// router
int check_route(char *str, t_thread_sockuser *thread);
t_user *user_sign_in(json_t *income_json, t_thread_sockuser *socket);
t_user *user_sign_up(json_t *income_json, t_thread_sockuser *socket);
void send_status(t_user *User, t_chat *Chat, int socketfd, int status, char *func);
int create_new_message(json_t *income_json, t_thread_sockuser *socket, t_user *User);

#endif
