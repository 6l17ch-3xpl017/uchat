#include "sophia_client.h"

/**
 * @brief function that takes 'key-value' pair and add it to the NoSQL database 'Sophia'
 * @param key - key that you want to add to the database
 * @param value - value that you want to add to the database
 * @return 0 if success, -1 if something went wrong
 */

int sophia_add(char *key, char *value) {
    void *db;
    void *env;
    void *document;
    int result;

    connect_sophia

    document = sp_document(db);
    sp_setstring(document, "key", key, 0);
    sp_setstring(document, "value", value, 0);
    result = sp_set(db, document);
    return result;
}
