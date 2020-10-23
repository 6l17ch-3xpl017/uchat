#include "client.h"

//ToDo: Rename this function GSList
//ToDo: Rework using gpointer
gpointer *get_widget(GSList *glist, char *needle)
{
    for (GSList *gtemp = glist; gtemp != NULL; gtemp = gtemp->next)
        if(strcmp(gtk_buildable_get_name(gtemp->data), needle) == 0)
            return gtemp->data;

    cmc_log_fatal("[Widget: %s didnt find]", needle); //ToDo: rework string
}

