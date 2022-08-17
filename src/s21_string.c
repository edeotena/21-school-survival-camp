#include <stdlib.h>
#include "s21_string.h"

int is_in(const char *str, char sym) {
    int res = 0;

    while (*str != '\0' && res == 0) {
        if (sym == *str) {
            res = 1;
        }
        str++;
    }

    return res;
}

char* s21_strtok(char *restrict str, const char *restrict sep) {
    static char *last_stop;

    if (str == NULL) {
        str = last_stop;
    }

    char *res = str;

    if (str != NULL) {
        int code = 0;

        while (code == 0) {
            if (is_in(sep, *str) == 1) {
                str++;
                res++;
            } else if (*str == '\0') {
                code = 1;
            } else {
                code = 2;
            }
        }

        if (code != 1) {
            code = 0;

            while (code == 0) {
                if (*str == '\0') {
                    last_stop = str;
                    code = 1;
                } else if (is_in(sep, *str) == 1) {
                    *str = '\0';
                    last_stop = str + 1;
                    code = 1;
                } else {
                    str++;
                }
            }
        } else {
            res = NULL;
        }
    } else {
        res = NULL;
    }

    return res;
}

int s21_strcmp_with_len(const char *str1, const char *str2, size_t len) {
    size_t i = 0;
    while (*str1 != '\0' && *str1 == *str2 && i < len - 1) {
        ++str1;
        ++str2;
        ++i;
    }

    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

char* s21_strstr(const char * str1, const char *str2) {
    char *res = NULL;
    if (s21_strlen(str1) != 0 && s21_strlen(str2) != 0) {
        size_t size = s21_strlen(str2);
        while (s21_strcmp_with_len(str1, str2, size) != 0 && *str1 != '\0') {
            ++str1;
        }

        if (s21_strcmp_with_len(str1 - 1, str2, size) != 0) {
            res = (char *)str1;
        }
    }

    return res;
}

char* s21_strchr(const char * str, int sym) {
    char *res = NULL;
    while (*str != sym && *str != '\0') {
        ++str;
    }

    if (*str == sym) {
        res = (char *)str;
    }

    return res;
}

char* s21_strcat(char *restrict str1, const char *restrict str2) {
    s21_strcpy(str1 + s21_strlen(str1), str2);
    return str1;
}

char* s21_strcpy(char *restrict str1, const char *restrict str2) {
    char *res = NULL;
    if (str1 != NULL) {
        res = str1;
        while (*str2 != '\0') {
            *str1 = *str2;
            ++str1;
            ++str2;
        }
        *str1 = '\0';
    }

    return res;
}

size_t s21_strlen(const char* str) {
    size_t len = 0;
    if (str != NULL) {
        while (str[len] != '\0') {
            ++len;
        }
    }

    return len;
}

int s21_strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str1 == *str2) {
        ++str1;
        ++str2;
    }

    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}
