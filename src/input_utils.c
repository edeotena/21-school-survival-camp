#include <stdio.h>
#include <string.h>

#include "input_utils.h"
#include "array_utils.h"

void remove_end_line(char *str);
int get_num(char *str, int *code, size_t *i);

int *safe_scan(int *len, int *code_ret) {
    int *res = NULL;
    char *buff = NULL;
    size_t cap_inp, len_inp = getline(&buff, &cap_inp, stdin);
    if (buff != NULL) {
        remove_end_line(buff);
        *len = 0;
        int cap = 3;
        for (size_t i = 0; i + 1 < len_inp && *code_ret != ERROR; ++i) {
            if (buff[i] != ' ') {
                int code = 0, new = get_num(buff + i, &code, &i);
                if (code != ERROR) {
                    code = add_to_arr(&res, new, len, &cap);
                    if (code == ERROR) {
                        *code_ret = ERROR;
                    }
                } else {
                    *code_ret = ERROR;
                }
            }
        }

        safe_free_str(&buff);
    }

    return res;
}

void remove_end_line(char *str) {
    size_t size = strlen(str);
    if (str[size - 1] == '\n') {
        str[size - 1] = '\0';
    }
}

int get_num(char *str, int *code, size_t *i) {
    int sum = 0, found = 0;
    while (*str >= '0' && *str <= '9') {
        sum = sum * 10 + (*str - '0');
        (str)++;
        (*i)++;
        found = 1;
    }

    if (found == 0) {
        *code = ERROR;
    }

    return sum;
}
