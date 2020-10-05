#include "header_db_dev.h"

int main() {

    init_database();

    t_user *User = (t_user *)malloc(sizeof(t_user));
    User->id = NULL;
    User->nickname = strdup("ushakov");
    User->password = strdup("qwerty");
    User->email = NULL;
    User->age = NULL;
    User->fullname = NULL;
    User->ph_number = NULL;
    User->user_photo = NULL;
    User->option = NULL;
    User->chats = NULL;

    user_in_db(User);
    get_chats_where_user(User);

//    printf("%s\n\n", user_in_db(User));
//    add_user_to_db(User);
    print_user_info(User);

//    t_chat *Chat = malloc(sizeof(t_chat));
//    Chat->chat_id = NULL;
//    Chat->chat_name = strdup("SChat");
//    Chat->admin_id = strdup("1");
//    Chat->chat_photo = strdup("/img/qq12xx.jpg");
//    Chat->option = NULL;

//    add_chat_to_db(Chat);
//    add_id_to_struct_Chat(Chat);
//    print_chat_info(Chat);

    return 0;
}
