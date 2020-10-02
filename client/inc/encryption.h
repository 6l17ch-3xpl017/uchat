#ifndef UCHAT_GUI_ENCRYPTION_H
#define UCHAT_GUI_ENCRYPTION_H


typedef struct s_encrypted_data
{
    void *data;
    int **seeds;
}              t_encrypted_data;

#endif //UCHAT_GUI_ENCRYPTION_H
