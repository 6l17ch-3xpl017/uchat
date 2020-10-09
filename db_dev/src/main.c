#include "header_db_dev.h"

int main() {

    init_database();

    t_user *User = (t_user *)malloc(sizeof(t_user));
    User->id = NULL;
    User->nickname = NULL;
    User->password = NULL;
    User->email = NULL;
    User->age = NULL;
    User->fullname = NULL;
    User->ph_number = NULL;
    User->user_photo = NULL;
    User->option = NULL;
    User->chats = NULL;
    User->number_of_chats = 0;

//    printf("%d\n\n", user_in_db(User));
//    user_in_db(User);

    printf("%d\n", add_user_to_db(User));
//    print_user_info(User);

//    t_chat *Chat = malloc(sizeof(t_chat));
//    Chat->chat_id = NULL;
//    Chat->chat_name = strdup("SChat");
//    Chat->admin_id = strdup("1");
//    Chat->chat_photo = strdup("/img/qq12xx.jpg");
//    Chat->option = NULL;

//    add_chat_to_db(Chat);
//    add_id_to_struct_Chat(Chat);
//    print_chat_info(Chat);

//    printf("number of chats: %d\n", User->number_of_chats);
//    t_chat *temp = User->chats;
//    for (int i = 0; i < User->number_of_chats; i++) {
//        printf("%s\n",temp->chat_name);
//        temp = temp->next;
//    }


    printf("\n\n");
    system("leaks -q db_dev");

    return 0;
}

