#include "header_db_dev.h"

//TODO correct the mistakes

int delete_user(t_user *User) { // has leaks
    if (!User->id)
        return id_can_not_be_null;

    t_chat *cursor = User->chats;
    for (int i = 0; i < User->number_of_chats; i++) {
        if (get_number_of_users_in_chat(cursor) == 2)
            delete_chat_from_db(cursor);
        else {
            if (is_admin(User) == 1)
                change_admin_randomly(cursor, User->id); // has bugs
            update_all_messages_by_deleted_user_in_chat(cursor, User->id);
            update_user_id_in__chat_user__(cursor, User->id);
        }
        cursor = cursor->next;
    }

    update_password_of_user(User, "1");
    update_email_of_user(User, NULL);
    update_age_of_user(User, NULL);
    update_fullname_of_user(User, NULL);
    update_phone_number_of_user(User, NULL);
    update_photo_of_user(User, NULL);
    update_user_id(User);

    return success;
}
