#include "client.h"
#include "page_selector.h"
#include "macro_collections.h"

//ToDo: Rework this function using memset
/**
 * Function initialize login_page struct and malloc memory
 * @param login_page
 */
static t_login_page *init_struct(void)
{
    cmc_log_info("[Start login_page struct initialization]");

    t_login_page *login_page = malloc(sizeof(t_login_page));

    if (!login_page)
        cmc_log_error("[login_page creation fail]");
    else
    {
        login_page->window = NULL;
        login_page->grid = NULL;
        login_page->label_user = NULL;
        login_page->label_pass = NULL;
        login_page->username = NULL;
        login_page->pass = NULL;
        login_page->sign_in_button = NULL;
        login_page->sign_up_button = NULL;

        cmc_log_info("[Finish login_page struct initialization]");
    }

    return login_page;
}

/**
 * Function initialize login_page
 * @return
 */
t_login_page *init_login_page(void)
{
    t_login_page *login_page = init_struct();
    /* Window Creation */
    cmc_log_info("[login_page->windows creation]");

    login_page->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(login_page->window), "Login page");
    gtk_window_set_position(GTK_WINDOW(login_page->window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(login_page->window), 25);
    gtk_window_set_resizable(GTK_WINDOW(login_page->window), FALSE);

    if (login_page->window != NULL)
        cmc_log_info("[login_page->window creation success]");
    else
        cmc_log_warn("[login_page->window creation fail]");
    /*-----------------*/

    /* Grid Creation */
    cmc_log_info("[login_page->grid creation]");

    login_page->grid = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(login_page->grid), 4);
    gtk_container_add(GTK_CONTAINER(login_page->window), login_page->grid);

    if (login_page->grid != NULL)
        cmc_log_info("[login_page->grid creation success]");
    else
        cmc_log_warn("[login_page->grid creation fail]");
    /*--------------*/

    /* Label Creation */
    cmc_log_info("[login_page->lable_user creation]");

    login_page->label_user = gtk_label_new("Username  ");

    if (login_page->label_user != NULL)
        cmc_log_info("[login_page->lable_user creation success]");
    else
        cmc_log_warn("[login_page->lable_user creation fail]");

    cmc_log_info("[login_page->lable_pass creation]");

    login_page->label_pass = gtk_label_new("Password  ");

    if (login_page->label_pass != NULL)
        cmc_log_info("[login_page->lable_pass creation success]");
    else
        cmc_log_warn("[login_page->lable_pass creation fail]");
    /*----------------*/

    /* Entry Creation */

    /* UserName */
    cmc_log_info("[login_page->username creation]");

    login_page->username = gtk_entry_new();

    gtk_entry_set_placeholder_text(GTK_ENTRY(login_page->username), "Username");
    gtk_grid_attach(GTK_GRID(login_page->grid), login_page->label_user, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(login_page->grid), login_page->username, 1, 1, 2, 1);

    if (login_page->username != NULL)
        cmc_log_info("[login_page->username creation success]");
    else
        cmc_log_warn("[login_page->username creation fail]");

    /* Password */
    cmc_log_info("[login_page->pass creation]");

    login_page->pass = gtk_entry_new();

    gtk_entry_set_placeholder_text(GTK_ENTRY(login_page->pass), "Password");
    gtk_grid_attach(GTK_GRID(login_page->grid), login_page->label_pass, 0, 2, 1, 1);
    gtk_entry_set_visibility(GTK_ENTRY(login_page->pass), 0);
    gtk_grid_attach(GTK_GRID(login_page->grid), login_page->pass, 1, 2, 1, 1);

    if (login_page->pass != NULL)
        cmc_log_info("[login_page->pass creation success]");
    else
        cmc_log_warn("[login_page->pass creation fail]");

    /*----------------*/

    /* Button Creation */
    cmc_log_info("[login_page->sign_in_button creation]");

    login_page->sign_in_button = gtk_button_new_with_label("Log in");

    if (login_page->sign_in_button != NULL)
        cmc_log_info("[login_page->sign_in_button creation success]");
    else
        cmc_log_warn("[login_page->sign_in_button creation fail]");

    cmc_log_info("[login_page->sign_up_button creation]");

    login_page->sign_up_button = gtk_button_new_with_label("Sign up");

    if (login_page->sign_up_button != NULL)
        cmc_log_info("[login_page->sign_up_button creation success]");
    else
        cmc_log_warn("[login_page->sign_up_button creation fail]");

    /*----------------*/

    return login_page;
}
