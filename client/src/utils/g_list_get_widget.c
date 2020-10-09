#include "client.h"

gpointer g_list_get_widget(GList *glist, char *needle)
{
    for (GList *gtemp = glist; gtemp != NULL; gtemp = gtemp->next)
        if(strcmp(gtk_buildable_get_name(gtemp->data), needle) == 0)
            return gtemp->data;

    cmc_log_fatal("[Widget: %s didnt find]", needle); //ToDo: rework string
}
