#include "client.h"

/**
 * @brief Function fills login_page struct with page data
 * @author dushakov
 * @return a filled structure
 */
static t_page *init_page(char *page_file_path)
{

    if(!page_file_path)
        cmc_log_fatal("page_file_path is empty");

    t_page *login_page = calloc(1, sizeof(t_page));
    login_page->widgets_count = 1;

    login_page->widgets = create_window(page_file_path);

//    login_page->widgets_names = malloc(sizeof(char *) * login_page->widgets_count);
//
//    //ToDo: rework this
//    for (GSList *gtemp = login_page->widgets; gtemp != NULL; gtemp = gtemp->next)
//    {
//        login_page->widgets_names[login_page->widgets_count - 1] = strdup(gtk_buildable_get_name(gtemp->data));
//        login_page->widgets_names = realloc(login_page->widgets_names, ++login_page->widgets_count);
//    }

    return login_page;
}

/**
 * Functions select page to show
 * @return result code
 */
void *select_page(char *page_file_path)
{
    return init_page(page_file_path);
}
