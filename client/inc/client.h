#ifndef UCHAT_GUI_CLIENT_H
#define UCHAT_GUI_CLIENT_H

#define CMC_LOG_COLOR

#include <gtk/gtk.h>

#define DEBUG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
//#import "Macros.h"
#pragma clang diagnostic pop
#include "utl/log.h"

typedef struct s_user_data
{
    char *type;

    const gchar *login;
    const gchar *pass;

    char *options;
}               t_user_data;

#endif //UCHAT_GUI_CLIENT_H
