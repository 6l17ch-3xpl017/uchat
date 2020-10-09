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
#include<netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/stat.h>
#include <syslog.h>
#include <time.h>

enum status {
    unknown_error = -10,
    not_reg_user = -4,
    ok_check_route = 5,
    ok = 7,
};

typedef struct s_thread_sockuser {
    int socket;
    char *user;
} t_thread_sockuser;

// router
int check_route(char *str, t_thread_sockuser *thread);
bool user_sign_in(json_t *income_json, t_thread_sockuser *socket);
bool user_sign_up(json_t *income_json, t_thread_sockuser *socket);
void send_json_to_socket(int socketfd, int status, char *func);

#endif
