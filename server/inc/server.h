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


typedef struct s_thread_sockuser {
    int socket;
    char *user;
    struct s_thread_sockuser *next;
} t_thread_sockuser;

// router
void check_route(char *str, int socket);
bool user_sign_in(json_t *income_json);
bool user_sign_up(json_t *income_json);

#endif
