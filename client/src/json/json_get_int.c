#include "client.h"

int json_get_int(json_t *root, char *key, int mode)
{
    json_t *tmp_obj = json_object_get(root, key);
    if (mode)
    {
        const char *tmp_result = NULL;
        tmp_result = json_string_value(tmp_obj);
        return atoi(tmp_result);
    }
    return json_integer_value(tmp_obj);
}
