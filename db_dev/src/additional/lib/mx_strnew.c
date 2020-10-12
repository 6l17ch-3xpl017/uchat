#include "header_db_dev.h"

char *mx_strnew(int size) {
    if (size >= 0) {
        char *s = (char *) malloc(sizeof(char) * (size + 1));
        for (int i = 0; i < size + 1; i++) {
            s[i] = '\0';
        }
        return s;
    }
    return NULL;
}
