#include "header_db_dev.h"

void mx_pop_back_for_chat(t_chat **head) {
    t_chat *temp = NULL;

    if (head == NULL || *head == NULL)
        return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
        temp = *head;
        while (temp && temp->next->next != NULL)
            temp = temp->next;
        if (temp->chat_id)
            mx_strdel(&temp->chat_id);
        if (temp->chat_name)
            mx_strdel(&temp->chat_name);
        if (temp->admin_id)
            mx_strdel(&temp->admin_id);
        if (temp->chat_photo)
            mx_strdel(&temp->chat_photo);
        if (temp->option)
            mx_strdel((char **)(&temp->option));
        free(temp->next);
        temp->next = NULL;
    }
}
