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
#include <time.h>
#include <stdarg.h>

 struct s_user;

typedef struct s_message {
    struct s_message *next;
    time_t time;
    int changed;
    char *message_id;
    char *message_owner_id;
    char *chat_id;
    char *message_content;
    char *option;
}              t_message;


typedef struct s_chat {
    struct s_user *user_in_chat;
    struct s_chat *next;
    struct s_message *next_message;
    int number_of_messages;
    int number_of_users;
    void *option;
    char *chat_id;
    char *chat_name;
    char *admin_id;
    char *chat_photo;
}              t_chat;

typedef struct s_user {
    struct s_user *next;
    struct s_chat *chats;
    int number_of_chats;
    void *option;
    char *id;
    char *nickname;
    char *password;
    char *email;
    char *age;
    char *fullname;
    char *ph_number;
    char *user_photo;
}              t_user;


typedef struct s_password {
    char *password;
}              t_password;

typedef struct s_chats_id {
    int number_of_chats;
    char **chat_id;
}              t_chats_id;

typedef struct s_user_id {
    int number_of_users;
    char **user_id;
}              t_user_id;

typedef struct s_messages_id {
    int number_of_messages;
    char **message_id;
}              t_messages_id;


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

enum chat_update {
    chat_name_can_not_be_null = 140,
    chat_does_not_exist = 141,
    admin_id_can_not_be_null = 142
};
// -----------------------------------------------------------------------


// ------------------------------SQLITE3_LIB------------------------------
// CREATE
int init_database();
int add_user_to_db(t_user *User);
int add_chat_to_db(t_chat *Chat);
int add_message_to_db(t_message *Message);
int add_user_in_chat(t_user *User, t_chat *Chat);

// DELETE
void drop_all();
int delete_user(t_user *User);
int delete_chat_from_db(t_chat *Chat);

//INSERT
int user_in_db(t_user *User);
int populate_User_struct(t_user *User);
void init_chat_struct(t_chat *Chat);
void init_message_struct(t_message *Message);
void init_user_struct(t_user *User);
int get_chats_where_user(t_user *User);
int check_valid_data_for_sign_up(t_user *User);
void add_id_to_struct_User(t_user *User);
void add_id_to_struct_Chat(t_chat *Chat);
void add_id_to_struct_Message(t_message *Message);
void mx_del_chat_list(t_chat *list, int leng);
void mx_pop_back_for_chat(t_chat **head);
int get_all_messages_from_db(t_chat *Chat);
int get_users_list_for_chat(t_chat *Chat);

// UPDATE
// user
int update_nickname_of_user(t_user *User, char *new_nickname);
int update_password_of_user(t_user *User, char *new_password);
int update_email_of_user(t_user *User, char *new_email);
int update_age_of_user(t_user *User, char *new_age);
int update_fullname_of_user(t_user *User, char *new_fullname);
int update_phone_number_of_user(t_user *User, char *new_phone_number);
int update_photo_of_user(t_user *User, char *new_photo);

// chat
void refresh_data_after_chat_update(t_chat *Chat, sqlite3 *db);
int update_chat_name(t_chat *Chat, char *new_chat_name);
int update_admin_id_of_chat(t_chat *Chat, char *new_admin_id);
int update_chat_photo(t_chat *Chat, char *new_photo_of_chat);
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

char *make_sql_request(char **dst, char *body, ...);


#endif //UCHAT_HEADER_DB_DEV_H

