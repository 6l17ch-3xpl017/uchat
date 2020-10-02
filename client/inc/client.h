#ifndef UCHAT_GUI_CLIENT_H
#define UCHAT_GUI_CLIENT_H

#define CMC_LOG_COLOR

#include <gtk/gtk.h>

typedef struct s_user_data
{
    char *type;

    const gchar *login;
    const gchar *pass;

    char *options;
}               t_user_data;

#endif //UCHAT_GUI_CLIENT_H
