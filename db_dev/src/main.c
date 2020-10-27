#include "header_db_dev.h"

//TODO make function that update chat's info, message's info, delete user from chat, check segmentation fault in all updates when User wasn't signed in

int main() {

decoding_enum(init_database());
//
//    t_user *User = (t_user *)malloc(sizeof(t_user));
//    User->id = NULL;
//    User->nickname = strdup("imarchenko");
//    User->password = strdup("qwerty");
//    User->email = strdup("anech@gmail.com");
//    User->age = strdup("17");
//    User->fullname = strdup("Andrey Nechytail");
//    User->ph_number = strdup("+380 67 588 47 66");
//    User->user_photo = strdup("img/345678.jpg");
//    User->option = NULL;
//    User->chats = NULL;
//    User->number_of_chats = 0;
//
    t_message *Message = (t_message *)malloc(sizeof(t_message));
    Message->message_id = NULL;
    Message->message_owner_id = strdup("1");
    Message->chat_id = strdup("1");
    Message->message_content = strdup("call");
    Message->time = 316326;
    Message->changed = 0;
    Message->option = NULL;



//    decoding_enum(user_in_db(User));
//    decoding_enum(update_photo_of_user(User, "img/photo/23492394.png"));
//    print_user_info(User);
//    if (User->chats->chat_photo)
//        printf("before : %s\n", User->chats->chat_photo);
//    else
//        printf("before : <null>\n");
//    decoding_enum(update_chat_photo(User->chats, "/img/new_photo.png"));
//    if (User->chats->chat_photo)
//        printf("after : %s\n", User->chats->chat_photo);
//    else
//        printf("after : <null>\n");

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

//    int a = get_all_messages_from_struct(User->chats);
//    if (a == success) {
//        t_message *iterator = User->chats->next_message;
//        for (int i = 0; i < User->chats->number_of_messages; ++i) {
//            printf("- %s\n", iterator->message_content);
//            iterator = iterator->next;
//        }
//    }

    add_message_to_db(Message);
    //printf("%s\n", Message->message_id);
    //printf("\n\n");
    system("leaks -q db_dev");



    return 0;
}

