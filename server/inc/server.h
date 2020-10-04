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

typedef struct s_use_mutex {
    pthread_mutex_t mutex;
} t_use_mutex;

// router
void check_route(char *str);
bool user_sign_in(json_t *income_json);
bool user_sign_up(json_t *income_json);

#endif
