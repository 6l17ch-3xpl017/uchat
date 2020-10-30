#include "client.h"

static void *u_get(char *field_name, char *name, void *user_attr_data)
{
    return strcmp(field_name, name) == 0 ? user_attr_data : NULL;
}

static void *u_set(char *field_name, char *name, void *user_attr_data, void *data)
{   //ToDo: Free unused memory
    return strcmp(field_name, name) == 0 ? user_attr_data = data : NULL;
}

static void *iterate_over_user_attr(struct s_user_attr *user_attr, char *field_name, int operation, void *data)
{
    void *result = NULL;
#define X(type, name) \
                         result = operation == U_GET ? u_get(field_name, #name, user_attr->name): u_set(field_name, #name, user_attr->name, data);
    USER_FIELDS
#undef X
    return result;
}
