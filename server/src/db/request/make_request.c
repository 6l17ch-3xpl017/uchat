#include "header_db_dev.h"

static int mx_count_substr(const char *str, const char *sub) {
    int i = 0;

    if (str == NULL || sub == NULL)
        return -1;
    if (strlen(str) >= strlen(sub)) {
        while (*str) {
            if (!strncmp((char *)str, (char *)sub, strlen(sub)))
                i++;
            str++;
        }
    }
    return i;
}

static char *mx_replace_one_substr(const char *str, const char *sub, const char *replace) {
    int sum = (int)(strlen(replace) - strlen(sub));
    int len = (int)strlen(str) + mx_count_substr(str, sub) * sum;
    char *memory = mx_strnew(len);
    int stop = false;

    if (!str || !sub || !replace || strlen(str) <= strlen(sub))
        return NULL;
    else {
        for (int i = 0; i < len; i++, str++) {
            if (!stop) {
                if (!strncmp((char *) str, (char *) sub, strlen(sub))) {
                    stop = true;
                    str += strlen(sub);
                    for (int j = 0; j < (int)strlen(replace); i++, j++)
                        memory[i] = replace[j];
                }
            }
            memory[i] = *str;
        }
        return memory;
    }
}

/**
 * @brief Function 'make_sql_request' - takes all information about request that you need and return you finished
 *        request for database. Dont use '' in parameter body! If values != NULL, function will read it automatically.
 * @param dst - Pointer to string where 'make_sql_request' returns result of work.
 * @param body - Pattern of request. All '%s' will be changed.
 * @param ... - Values which you want to use instead of '%s'.
 */

char *make_sql_request(char **dst, char *body, ...) {
    int number_of_args = mx_count_substr(body, "%s");
    char *current_argument;
    char *temporary_result;
    char *assistant;
    va_list list;

    va_start(list, body);
    *dst = strdup(body);

    for (int i = 0; i < number_of_args; i++) {
        current_argument = va_arg(list, char *);
        if (!current_argument) {
            temporary_result = mx_replace_one_substr(*dst, "%s", "NULL");
            mx_strdel(dst);
            *dst = strdup(temporary_result);
            mx_strdel(&temporary_result);
        }
        else {
            assistant = mx_replace_one_substr("'%s'", "%s", current_argument);
            temporary_result = mx_replace_one_substr(*dst, "%s", assistant);
            mx_strdel(&assistant);
            mx_strdel(dst);
            *dst = strdup(temporary_result);
            mx_strdel(&temporary_result);
        }
    }

    va_end(list);
    return *dst;
}
