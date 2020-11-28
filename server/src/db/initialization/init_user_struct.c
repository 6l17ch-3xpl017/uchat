#include "header_db_dev.h"

void init_user_struct(t_user *User) {
    User->id = NULL;
    User->nickname = NULL;
    User->password = NULL;
    User->email = NULL;
    User->age = NULL;
    User->fullname = NULL;
    User->ph_number = NULL;
    User->user_photo = NULL;
    User->option = NULL;
    User->country = NULL;
    User->next = NULL;
    User->chats = NULL;
    User->number_of_chats = 0;
}
