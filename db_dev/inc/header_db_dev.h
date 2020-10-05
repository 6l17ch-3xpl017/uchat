#ifndef UCHAT_HEADER_DB_DEV_H
#define UCHAT_HEADER_DB_DEV_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
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
    char *id;
    char *nickname;
    char *password;
    char *email;
    char *age;
    char *fullname;
    char *ph_number;
    char *user_photo;
    void *option;
    struct s_user *next;
    char **chats;
    int number_of_chats;
}              t_user;

typedef struct s_chat {
    char *chat_id;
    char *chat_name;
    char *admin_id;
    char *chat_photo;
    void *option;
}              t_chat;

typedef struct s_password {
    char *password;
}              t_password;

char *mx_itoa(int number);
void mx_del_strarr(char ***arr);
void mx_strdel(char **str);
char *mx_strnew(int size);

char *user_in_db(t_user *User);
void populate_User_struct(t_user *User);
void init_database();
void drop_all();
void get_chats_where_user(t_user *User);

void add_user_to_db(t_user *User);
void add_chat_to_db(t_chat *Chat);

void print_user_info(t_user *User);
void print_chat_info(t_chat *Chat);

void add_id_to_struct_User(t_user *User);
void add_id_to_struct_Chat(t_chat *Chat);

#endif //UCHAT_HEADER_DB_DEV_H
