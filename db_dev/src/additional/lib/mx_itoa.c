#include "header_db_dev.h"

char *mx_itoa(int number) {
    if (number == -2147483648) {
        char *result = malloc(12);
        result = strcpy(result,"-2147483648");
        return result;
    }

    if (number == 0) {
        char *result = malloc(2);
        result = strcpy(result,"0");
        return result;
    }
    int length = 0;
    bool isNegative = false;
    if (number < 0) {
        length++;
        isNegative = true;
        number = -number;
    }

    int tempNumber = number;

    while (tempNumber != 0) //Counting the length of number in digits plus '-' sign in the upper cycle
    {
        tempNumber /= 10;
        length++;
    }

    char *string = malloc(sizeof(char) * length + 1);

    string[length] = '\0';

    for (int i = 0; number != 0; i++) {
        string[length - 1 - i] = (char) ((number % 10) + 48);
        number /= 10;
    }
    if (isNegative)
        string[0] = '-';
    return string;
}
