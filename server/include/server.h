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

typedef struct s_user {
    char *nickname;
    char *password;
    char *email;
    int age;
    char *fullname;
    char *ph_number;
    char *user_photo;
    void *option;
    struct s_user *next;
} t_user;

void check_route(char *str);

#endif
