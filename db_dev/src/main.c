//
// Created by Illia Marchenko on 9/24/20.
//

#include "header_db_dev.h"

int main() {
    init_database();
    t_user *User = (t_user *)malloc(sizeof(t_user));
    User->nickname = strdup("imarchenko");
    User->password = strdup("qwerty1234");
    User->email = "imarchenko02@gmail.com";
    User->age = "18";
    User->fullname = "ILay Marchenko";
    User->ph_number = "+380 63 599 64 22";
    User->user_photo = "/photos/imarchenko.jpg";
    User->option = NULL;
    add_user_to_db(User);
    return 0;
}
