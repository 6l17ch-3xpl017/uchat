//
// Created by Illia Marchenko on 9/24/20.
//

#ifndef UCHAT_HEADER_DB_DEV_H
#define UCHAT_HEADER_DB_DEV_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <grp.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <sqlite3.h>

typedef struct s_sqlite_request {
    char *error_message;
    char **result;
    char *request;
}              t_sqlite_request;

typedef struct s_user {
    char *nickname;
    char *password;
    char *email;
    char *age;
    char *fullname;
    char *ph_number;
    char *user_photo;
    void *option;
    struct s_user *next;
} t_user;

char *mx_itoa(int number);
bool if_user_in_db(char *nickname);
void init_database();
void add_user_to_db(t_user *User);

#endif //UCHAT_HEADER_DB_DEV_H
