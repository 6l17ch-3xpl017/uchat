#include "client.h"
#include "encryption.h"

static char *encode(char *pass)
{
    printf("Original pass: %s\n", pass);

    size_t seed = (int)(rand()) % 100000000 + (int)(rand()) % 100000000;
    size_t pass_len = strlen(pass);

    for (size_t i = 0, local_seed = seed; i < pass_len; i++) {
        pass[i] = pass[i] ^ (((local_seed % 1000) + (local_seed / 1000)));
        local_seed /= 10;
    }

    printf("Encoded pass: %s\n", pass);

    for (size_t i = 0, local_seed = seed; i < pass_len; i++) {
        pass[i] = pass[i] ^ (((local_seed % 1000) + (local_seed / 1000)));
        local_seed /= 10;
    }

    printf("Decoded pass pass: %s\n", pass);

    return pass;
}

t_encrypted_data *super_secret_encryption_method(t_encrypted_data *encryptedData)
{
    size_t seed = (int)(rand()) % 100000000 + (int)(rand()) % 100000000;
    size_t pass_len = strlen(encryptedData->data);
    size_t *data = (size_t *)encryptedData->data;

    for (size_t i = 0, local_seed = seed; i < pass_len; i++) {
        data[i] = data[i] ^ (((local_seed % 1000) + (local_seed / 1000)));
        local_seed /= 10;
    }

    encryptedData->data = data;

    return encryptedData;
}
