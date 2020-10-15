#ifndef UCHAT_HEADER_DB_DEV_H
#define UCHAT_HEADER_DB_DEV_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
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
    char *ph_number; //todo change
    char *user_photo; //todo change
    void *option;
    struct s_user *next;
    struct s_chat *chats;
    int number_of_chats;
}              t_user;

typedef struct s_message {
    char *message_id;
    char *message_owner_id;
    char *chat_id;
    char *message_content;
    char *time;
    char *changed; //todo change
    char *option; //todo change
}              t_message;

typedef struct s_password {
    char *password;
}              t_password;

typedef struct s_chats_id {
    char **chat_id;
    int number_of_chats;
}              t_chats_id;


// --------------------------RESULTS OF FUNCTIONS------------------------
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
    id_can_not_be_null = 111,
    phone_number_was_already_signed_up = 112,
    success = 113,
    nickname_and_password_can_not_be_null = 114,
    chat_name_and_admin_id_can_not_be_null = 115,
    request_failed = 116,
    message_cannot_be_empty = 122
};

enum db_init {
    can_not_create_users_table = 117,
    can_not_create_chats_table = 118,
    can_not_create_chat_user_table = 119,
    can_not_create_messages_table = 120,
    database_was_connected = 121
};
// -----------------------------------------------------------------------


// ------------------------------SQLITE3_LIB------------------------------
// CREATE
int init_database();
int add_user_to_db(t_user *User);
int add_chat_to_db(t_chat *Chat);
int add_user_in_chat(t_user *User, t_chat *Chat);

// DELETE
void drop_all();
int delete_user(t_user *User);

//INSERT
int user_in_db(t_user *User);
int populate_User_struct(t_user *User);
void init_chat_struct(t_chat *Chat);
int get_chats_where_user(t_user *User);
int check_valid_data_for_sign_up(t_user *User);
void add_id_to_struct_User(t_user *User);
void add_id_to_struct_Chat(t_chat *Chat);
void mx_del_chat_list(t_chat *list, int leng);
void mx_pop_back_for_chat(t_chat **head);

// UPDATE
int update_nickname_of_user(t_user *User, char *new_nickname);
int update_password_of_user(t_user *User, char *new_password);
int update_email_of_user(t_user *User, char *new_email);
int update_age_of_user(t_user *User, char *new_age);
int update_fullname_of_user(t_user *User, char *new_fullname);
int update_phone_number_of_user(t_user *User, char *new_phone_number);
// -----------------------------------------------------------------------

// ------------------------------ADDITIONAL-------------------------------
// LIBRARY
char *mx_itoa(int number);
void mx_del_strarr(char ***arr);
void mx_strdel(char **str);
char *mx_strnew(int size);

// SQL
void decoding_enum(int enum_number);
void print_user_info(t_user *User);
void print_chat_info(t_chat *Chat);
// -----------------------------------------------------------------------


#endif //UCHAT_HEADER_DB_DEV_H
