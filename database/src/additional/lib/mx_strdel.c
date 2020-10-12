#include "header_db_dev.h"

void mx_strdel(char **str) {
    if (str && *str)
        free(*str);
    *str = NULL;
}

