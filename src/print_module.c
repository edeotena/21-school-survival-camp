#include <stdio.h>
#include <time.h>

#include "print_module.h"

void print_log(int(*print) (char), char* message) {
    int i = 0;
    while (Log_prefix[i] != '\0') {
        print(Log_prefix[i]);
        ++i;
    }

    print(' ');

    time_t current_time;
    struct tm *time_info;
    char timeString[9];

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);

    i = 0;
    while (timeString[i] != '\0') {
        print(timeString[i]);
        ++i;
    }

    print(' ');

    while (*message != '\0') {
        print(*message);
        ++message;
    }
}

int print_char(char ch) {
    return putchar(ch);
}
