#include "parse.h"
#include "structs.h"
#include <string.h>

double get_num(const char *str, int *code, size_t *j) {
    size_t size = strlen(str), i = 0, k = 0;
    double res = 0;

    while (str[i] <= '9' && str[i] >= '0' && i < size) {
        res = res * 10 + str[i] - '0';
        ++i;
    }

    if (str[i] == '.') {
        k = i + 1;
        int digit = 10;
        while (str[k] <= '9' && str[k] >= '0' && k < size) {
            res += (double)(str[k] - '0') / digit;
            digit *= 10;
            ++k;
        }
    }

    if (k != 0) {
        (*j) += k - 1;
    } else {
        (*j) += i - 1;
    }

    if (i == 0 || k == i + 1) {
        *code = ERROR;
    }

    return res;
}

char get_lex(const char *str, size_t *i) {
    char res = 0;
    size_t size = strlen(str);
    if (str[0] == 'x') {
        res = 'x';
    } else if (str[0] == '+') {
        res = '+';
    } else if (str[0] == '-') {
        res = '-';
    } else if (str[0] == '*') {
        res = '*';
    } else if (str[0] == '/') {
        res = '/';
    } else if (str[0] == '(') {
        res = '(';
    } else if (str[0] == ')') {
        res = ')';
    } else if (str[0] == '^') {
        res = '^';
    } else if (size >= 2 && str[0] == 's' && str[1] == 'i' && str[2] == 'n') {
        res = 's';
        (*i) += 2;
    } else if (size >= 2 && str[0] == 'c' && str[1] == 'o' && str[2] == 's') {
        res = 'c';
        (*i) += 2;
    } else if (size >= 2 && str[0] == 't' && str[1] == 'a' && str[2] == 'n') {
        res = 't';
        (*i) += 2;
    } else if (size >= 2 && str[0] == 'c' && str[1] == 't' && str[2] == 'g') {
        res = 'g';
        (*i) += 2;
    } else if (size >= 3 && str[0] == 's' && str[1] == 'q' && str[2] == 'r' && str[3] == 't') {
        res = 'q';
        (*i) += 3;
    } else if (size >= 1 && str[0] == 'l' && str[1] == 'n') {
        res = 'l';
        (*i) += 1;
    }
    return res;
}

queue *parse_to_lex(char *str) {
    queue *res = NULL;
    size_t size = strlen(str);
    int code = 0;

    if (str[size - 1] == '\n') {
        str[size - 1] = '\0';
        --size;
    }

    char last_sym = 0;
    for (size_t i = 0; i < size && code == 0; ++i) {
        if (str[i] != ' ') {
            char lex = get_lex(str + i, &i);
            if (lex != 0) {
                if ((lex == '-' && last_sym == '(') || (lex == '-' && i == 0)) {
                    add(&res, '~', 0, &code);
                } else {
                    last_sym = lex;
                    add(&res, lex, 0, &code);
                }
            } else {
                double num = get_num(str + i, &code, &i);
                if (code != ERROR) {
                    add(&res, 0, num, &code);
                    last_sym = 0;
                }
            }
        }
    }

    if (code == ERROR) {
        free_queue(&res);
    }

    return res;
}
