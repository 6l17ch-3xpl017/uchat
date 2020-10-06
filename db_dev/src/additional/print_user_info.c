#include "header_db_dev.h"

void print_user_info(t_user *User) {
    printf("id:            %s\n", User->id);
    printf("nickname:      %s\n", User->nickname);
    printf("password:      %s\n", User->password);
    printf("email:         %s\n", User->email);
    printf("age:           %s\n", User->age);
    printf("fullname:      %s\n", User->fullname);
    printf("ph_number:     %s\n", User->ph_number);
    printf("user_photo:    %s\n", User->user_photo);
    printf("option:        %s\n", (char *)User->option);
    if (User->number_of_chats != 0) {
        printf("chats_id:      %s\n", User->chats[0]);
        for (int i = 1; i < User->number_of_chats; i++) {
            printf("               %s\n", User->chats[i]);
        }
    }
}
