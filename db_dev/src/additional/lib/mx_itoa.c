#include "header_db_dev.h"

//static void mx_swap_char(char *s1, char *s2) {
//    char temp;
//    temp = *s1;
//    *s1 = *s2;
//    *s2 = temp;
//}
//
//char *mx_itoa(int number) {
//
//    long num = number;
//    long num1 = number;
//    int length = 0;
//    char temp;
//    int i = 0;
//    bool is_negative = false;
//    int begin;
//
//    if (num == 0)
//        return "0";
//
//    if (num1 < 0) {
//        num1 *= -1;
//        num *= -1;
//        i++;
//        length++;
//        is_negative = true;
//    }
//
//    while(num > 0) {
//        num /= 10;
//        length++;
//    }
//
//    char *result = (char *)malloc(sizeof(char) * length + 1);
//
//    if (i == 1)
//        result[length] = '-';
//
//    for (; i < length; ++i) {
//        temp = (num1 % 10) + 48;
//        num1 /= 10;
//        result[i] = temp;
//    }
//
//    int end = length;
//
//    if (is_negative) {
//        for(begin = 1; begin < end; begin++){
//            mx_swap_char(&result[begin], &result[end]);
//            end --;
//        }
//        result++;
//        result[length] = '\0';
//    }
//    else {
//        for(begin = 0; begin < end; begin++){
//            mx_swap_char(&result[begin], &result[end]);
//            end --;
//        }
//        result++;
//        result[length] = '\0';
//    }
//    //printf("itoa call returned %s\n", result);
//    return result;
//}

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
