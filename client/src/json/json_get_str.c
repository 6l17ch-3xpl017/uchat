#include "client.h"

char *json_get_str(json_t *root, char *key)
{
    json_t *tmp_obj = json_object_get(root, key);
    char *result = strdup(json_string_value(tmp_obj));

    return result;
}
