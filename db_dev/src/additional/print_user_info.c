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
    printf("\nnumber of chats:    %d\n", User->number_of_chats);
    t_chat *temp = User->chats;
    for (int i = 0; i < User->number_of_chats; i++) {
        if (i == 0) {
            printf("names of chats:");
            printf("     %s\n",temp->chat_name);
        }else
            printf("                    %s\n",temp->chat_name);
        temp = temp->next;
    }
}
