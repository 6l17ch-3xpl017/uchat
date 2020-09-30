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
}              t_user;

typedef struct s_chat {
    char *chat_name;
    char *admin_id;
    char *chat_photo;
    void *option;
}              t_chat;

typedef struct s_password {
    char *password;
}              t_password;

char *mx_itoa(int number);

char *user_in_db(t_user *User);
void init_database();
void add_user_to_db(t_user *User);
void add_chat_to_db(t_chat *Chat);
void drop_all();

#endif //UCHAT_HEADER_DB_DEV_H
