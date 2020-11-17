//#include "header_db_dev.h"
//
//int delete_user(t_user *User) {
//    sqlite3 *db;
//    int result;
//    char *request = NULL;
//
//    if (!User->id)
//        return id_can_not_be_null;
//
//    connect_to_db
//
//    t_chat *cursor = User->chats;
//    for (int i = 0; i < User->number_of_chats; i++) {
//        if (get_number_of_users_in_chat(cursor) == 2)
//            delete_chat_from_db(cursor);
//        else {
//            if (is_admin(User) == 1) {
//                change_admin_in_chat();
//                update_all_messages_by_deleted_user_in_chat();
//                change_in_chat_user();
//            }
//        }
//        cursor = cursor->next;
//    }
//
//    update_password_of_user(User, "1");
//    update_email_of_user(User, NULL);
//    update_age_of_user(User, NULL);
//    update_fullname_of_user(User, NULL);
//    update_phone_number_of_user(User, NULL);
//    update_photo_of_user(User, NULL);
//
//    update_user_id(User, new_id);
//
//    sqlite3_close(db);
//
//    if (result != SQLITE_OK)
//        return request_failed;
//    else
//        return success;
//}
