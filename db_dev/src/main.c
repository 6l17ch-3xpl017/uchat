#include "header_db_dev.h"

int main() {

    decoding_enum(init_database());

    t_user *User = (t_user *)malloc(sizeof(t_user));
    User->id = NULL;
    User->nickname = strdup("anechytail");
    User->password = strdup("qwerty");
    User->email = NULL;
    User->age = NULL;
    User->fullname = NULL;
    User->ph_number = NULL;
    User->user_photo = NULL;
    User->option = NULL;
    User->chats = NULL;
    User->number_of_chats = 0;

    decoding_enum(user_in_db(User));
    decoding_enum(update_photo_of_user(User, "img/photo/23492394.png"));
    print_user_info(User);

//    t_chat *Chat = malloc(sizeof(t_chat));
//    Chat->chat_id = NULL;
//    Chat->chat_name = strdup("test_chat_user");
//    Chat->admin_id = strdup("1");
//    Chat->chat_photo = strdup("/img/qqfgebcfex.jpg");
//    Chat->option = NULL;
//
//    add_chat_to_db(Chat);
//    print_chat_info(Chat);
//
//    decoding_enum(add_user_in_chat(User, Chat));


//    int i = 1;
//    get_all_messages_from_struct(User->chats);
//    t_message *temp = User->chats->next_message;
//    while (temp) {
//        printf("%d) - %s\n", i, temp->message_content);
//        temp = temp->next;
//        i++;
//    }


//    printf("\n\n");
//    system("leaks -q db_dev");


    return 0;
}

