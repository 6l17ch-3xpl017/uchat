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


typedef struct s_chat {
    char *chat_id;
    char *chat_name;
    char *admin_id;
    char *chat_photo;
    void *option;
    struct s_chat *next;
}              t_chat;

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
    struct s_chat *chats;
    int number_of_chats;
}              t_user;

typedef struct s_password {
    char *password;
}              t_password;

typedef struct s_chats_id {
    char **chat_id;
    int number_of_chats;
}              t_chats_id;

enum sing_in_sing_up_db {
    can_not_open_db = 101,
    nickname_and_email_can_not_be_null = 102,
    login_incorrect = 103,
    login_and_password_correct = 104,
    password_incorrect = 105,
    function_fail = 106,
    successfully_added_to_db = 107,
    can_not_add_to_database = 108,
    nickname_was_already_signed_up = 109,
    email_was_already_signed_up = 110,
    phone_number_was_already_signed_up = 112,
    success = 113,
    nickname_and_password_can_not_be_null = 114
};

//char *mx_itoa(int number);
//void mx_del_strarr(char ***arr);
//void mx_strdel(char **str);
//char *mx_strnew(int size);

int user_in_db(t_user *User);
void populate_User_struct(t_user *User);
void init_database();
void drop_all();
void get_chats_where_user(t_user *User);
int check_valid_data_for_sign_up(t_user *User);

int add_user_to_db(t_user *User);
void add_chat_to_db(t_chat *Chat);

void print_user_info(t_user *User);
void print_chat_info(t_chat *Chat);

void add_id_to_struct_User(t_user *User);
void add_id_to_struct_Chat(t_chat *Chat);

#endif //UCHAT_HEADER_DB_DEV_H
