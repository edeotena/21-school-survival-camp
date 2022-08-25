#include <stdlib.h>

#include "array_utils.h"

void safe_free_arr(int **arr) {
    if (*arr != NULL) {
        free(*arr);
        *arr = NULL;
    }
}

void safe_free_str(char **str) {
    if (*str != NULL) {
        free(*str);
        *str = NULL;
    }
}

int add_to_arr(int **res, int new, int* len, int *cap) {
    int code = 0;

    if (*len == *cap || *res == NULL) {
        *cap *= 2;
        int *temp = (int *) realloc(*res, *cap * sizeof(int));
        if (temp != NULL) {
            *res = temp;
        } else {
            free(*res);
            *res = NULL;
            code = ERROR;
        }
    }

    if (*res != NULL) {
        (*res)[(*len)++] = new;
    }

    return code;
}

