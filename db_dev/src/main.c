//
// Created by Illia Marchenko on 9/24/20.
//

#include "../inc/header_db_dev.h"

int main() {
    init_database();
    t_user *User = (t_user *)malloc(sizeof(t_user));
    User->nickname = strdup("imarchenko");
//    User->nickname = NULL;

    User->password = strdup("qwerty");

    User->email = "imar@gmail.com";
//    User->email = NULL;

    User->age = "18";
    User->fullname = "Ilay Marchenko";
    User->ph_number = "+380 63 599 64 22";
    User->user_photo = "/photos/imarchenko.jpg";
    User->option = NULL;
    //add_user_to_db(User);
    //printf("%s\n\n", user_in_db(User));
    //system("leaks -q UCHAT");
    return 0;
}
