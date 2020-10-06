#include "header_db_dev.h"

int main() {

    init_database();

    t_user *User = (t_user *)malloc(sizeof(t_user));
    User->id = NULL;
    User->nickname = strdup("dushakov");
    User->password = strdup("qwerty");
    User->email = strdup("deniska@gmail.com");
    User->age = strdup("23");
    User->fullname = NULL;
    User->ph_number = NULL;
    User->user_photo = strdup("img/photo12344312");
    User->option = NULL;
    User->chats = NULL;

    printf("%s\n\n", user_in_db(User));

//    printf("%s\n\n", user_in_db(User));
//    add_user_to_db(User);
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

    system("leaks -q db_dev");

    return 0;
}
