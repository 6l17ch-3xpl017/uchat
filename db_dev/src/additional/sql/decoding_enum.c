#include "header_db_dev.h"

void decoding_enum(int enum_number) {
    if (enum_number == 101)
        printf("can_not_open_db\n");
    else if (enum_number == 102)
        printf("nickname_and_email_can_not_be_null\n");
    else if (enum_number == 103)
        printf("login_incorrect\n");
    else if (enum_number == 104)
        printf("login_and_password_correct\n");
    else if (enum_number == 105)
        printf("password_incorrect\n");
    else if (enum_number == 106)
        printf("function_fail\n");
    else if (enum_number == 107)
        printf("successfully_added_to_db\n");
    else if (enum_number == 108)
        printf("can_not_add_to_database\n");
    else if (enum_number == 109)
        printf("nickname_was_already_signed_up\n");
    else if (enum_number == 110)
        printf("email_was_already_signed_up\n");
    else if (enum_number == 111)
        printf("id_can_not_be_null\n");
    else if (enum_number == 112)
        printf("phone_number_was_already_signed_up\n");
    else if (enum_number == 113)
        printf("success\n");
    else if (enum_number == 114)
        printf("nickname_and_password_can_not_be_null\n");
    else if (enum_number == 115)
        printf("chat_name_and_admin_id_can_not_be_null\n");
    else if (enum_number == 116)
        printf("request_failed\n");
    else if (enum_number == 117)
        printf("can_not_create_users_table\n");
    else if (enum_number == 118)
        printf("can_not_create_chats_table\n");
    else if (enum_number == 119)
        printf("can_not_create_chat_user_table\n");
    else if (enum_number == 120)
        printf("can_not_create_messages_table\n");
    else if (enum_number == 121)
        printf("database_was_connected\n");
    else if (enum_number == 140)
        printf("chat_name_can_not_be_null\n");
    else if (enum_number == 141)
        printf("chat_does_not_exist\n");

}
