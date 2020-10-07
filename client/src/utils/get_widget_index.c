#include "client.h"

//ToDo: Rework using gpointer
gpointer *get_widget(GSList *glist, char *needle)
{
    for (GSList *gtemp = glist; gtemp != NULL; gtemp = gtemp->next)
        if(strcmp(gtk_buildable_get_name(gtemp->data), needle) == 0)
            return gtemp->data;

//    gtk_main();

//    for (GSList *gtemp = glist; gtemp != NULL; gtemp = gtemp->next)
//        if(strcmp(gtk_buildable_get_name(gtemp->data), needle) == 0) {
//            gtk_widget_show(GTK_WIDGET(gtemp->data));
//        }
//
//    gtk_main();

    cmc_log_fatal("[Widget: %s didnt find]", needle);
}

