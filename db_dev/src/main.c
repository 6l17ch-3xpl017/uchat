#include "../inc/header_db_dev.h"

int main() {

    init_database();

    t_user *User = (t_user *)malloc(sizeof(t_user));
    User->nickname = strdup("imarchenko");
    User->password = strdup("qwerty");
    User->email = "imarchenko@gmail.com";
    User->age = "18";
    User->fullname = "Ilay Marchenko";
    User->ph_number = "+380 63 599 64 22";
    User->user_photo = "/photos/imarchenko.jpg";
    User->option = NULL;

    //add_user_to_db(User);
    //printf("%s\n\n", user_in_db(User));

    t_chat *Chat = malloc(sizeof(t_chat));
    Chat->chat_name = strdup("FirstChat");
    Chat->admin_id = strdup("1");
    Chat->chat_photo = strdup("/img/qqxnexwx.jpg");
    Chat->option = NULL;

    //drop_all();
    add_chat_to_db(Chat);



    return 0;
}
