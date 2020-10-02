#ifndef UCHAT_GUI_PAGE_SELECTOR_H
#define UCHAT_GUI_PAGE_SELECTOR_H



typedef struct s_login_page
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *sign_in_button;
    GtkWidget *sign_up_button;
    GtkWidget *username;
    GtkWidget *pass;
    GtkWidget *label_user;
    GtkWidget *label_pass;
    char *type;
    int soketfd;

}              t_login_page;


void *select_page(int page_id, void *options);
t_login_page *init_login_page(void);

#endif
