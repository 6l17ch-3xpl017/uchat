#include "client.h"
#include "page_selector.h"


/**
 * Functions select page to show
 * @param page_id
 * @param options debug options
 * @return result code
 */
void *select_page(int page_id, void *options)
{

    if (page_id == 0)
        return init_login_page();

    return NULL;
}
