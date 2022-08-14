#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define LEN 100

int input_params(int *code, int *n, int *m);
int** input(int code, int n, int m);
int static_matrix(int n, int m);
void output(int **arr, int n, int m);
void free_matrix(int **arr, int code, int n);

int main() {
    int code, n, m;
    if (input_params(&code, &n, &m) == 0) {
        if (code != 1) {
            int** arr = input(code, n, m);
            if (arr != NULL) {
                output(arr, n, m);
                free_matrix(arr, code, n);
            } else {
                printf("n/a");
            }
        } else {
            if (static_matrix(n, m) != 0) {
                printf("n/a");
            }
        }
    } else {
        printf("n/a");
    }

    return 0;
}

void free_matrix(int **arr, int code, int n) {
    if (code == 4) {
        free(arr[0]);
        free(arr);
    } else if (code == 3) {
        for (int i = 0; i < n; ++i) {
            free(arr[i]);
        }
        free(arr);
    } else {
        free(arr);
    }

    return;
}

int input_params(int* code, int *n, int *m) {
    char sym = 0, ret_code = 0;
    int sc = scanf("%d%c", code, &sym);
    if (((sc == 1 && sym == 0) || (sc == 2 && sym == '\n')) &&
        *code > 0 && *code < 5) {
        sym = 0;
        sc = scanf("%d %d%c", n, m, &sym);
        if (!((sc == 2 && sym == 0) || (sc == 3 && sym == '\n')) || *n <= 0 ||
            *m <= 0 || (*code == 1 && *n > LEN && *m > LEN)) {
            ret_code = ERROR;
        }
    } else {
        ret_code = ERROR;
    }

    return ret_code;
}

int** input(int code, int n, int m)  {
    int **res = (int**) malloc(n * sizeof(int*) + n * m + sizeof(int));

    if (res != NULL) {
        int code_error = 0;
        if (code == 2) {
            int *ptr = (int*) (res + n);
            for (int i = 0; i < n; ++i) {
                res[i] = ptr + m * i;
            }
        } else if (code == 3) {
            for (int i = 0; i < n && code_error == 0; ++i) {
                res[i] = (int*) malloc(m * sizeof(int));
                if (res[i] == NULL) {
                    code_error = ERROR;
                    for (int j = 0; j <= i; ++j) {
                        free(res[i]);
                    }
                    free(res);
                }
            }
        } else if (code == 4) {
            int *values = (int*) malloc(n * m * sizeof(int));
            if (values != NULL) {
                for (int i = 0; i < n; ++i) {
                    res[i] = values + m * i;
                }
            } else {
                code_error = ERROR;
            }
        }

        if (code_error == 0) {
            for (int i = 0; i < n && code_error == 0; ++i) {
               for (int j = 0; j < m - 1 && code_error == 0; ++j) {
                    if (scanf("%d", &res[i][j]) != 1) {
                        code_error = ERROR;
                        free_matrix(res, code, n);
                        res = NULL;
                    }
                }

                if (code_error == 0) {
                    char sym, sc = scanf("%d%c", &res[i][m - 1], &sym);
                    if (!((sc == 1 && !sym) || (sc == 2 && sym == '\n'))) {
                        code_error = ERROR;
                        free_matrix(res, code, n);
                        res = NULL;
                    }
                }
            }
        }
    }

    return res;
}

void output(int **arr, int n, int m) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            printf("%d ", arr[i][j]);
        }

        printf("%d\n", arr[i][m-1]);
    }

    for (int j = 0; j < m - 1; ++j) {
        printf("%d ", arr[n - 1][j]);
    }
    printf("%d", arr[n - 1][m - 1]);
}

int static_matrix(int n, int m) {
    int res[LEN][LEN], code_error = 0;
    for (int i = 0; i < n && code_error == 0; ++i) {
        for (int j = 0; j < m - 1 && code_error == 0; ++j) {
            if (scanf("%d", &res[i][j]) != 1) {
                code_error = ERROR;
            }
        }

        if (code_error == 0) {
            char sym, sc = scanf("%d%c", &res[i][m - 1], &sym);
            if (!((sc == 1 && !sym) || (sc == 2 && sym == '\n'))) {
                code_error = ERROR;
            }
        }
    }

    if (code_error == 0) {
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < m - 1; ++j) {
                printf("%d ", res[i][j]);
            }

            printf("%d\n", res[i][m - 1]);
        }

        for (int j = 0; j < m - 1; ++j) {
            printf("%d ", res[n - 1][j]);
        }
        printf("%d", res[n - 1][m - 1]);
    }

    return code_error;
}
