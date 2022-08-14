#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define LEN 100

int input_params(int *code, int *n, int *m);
int** input(int code, int n, int m);
void output(int **arr, int n, int m);
void free_matrix(int **arr, int code, int n);
void sort(int **arr, int n, int m);
void swap_arr(int *a, int *b, int size);

int main() {
    int code, n, m;
    if (input_params(&code, &n, &m) == 0) {
        int** arr = input(code, n, m);
        if (arr != NULL) {
            sort(arr, n, m);
            output(arr, n, m);
            free_matrix(arr, code, n);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }

    return 0;
}

int get_sum(const int *a, int size) {
    int sum = 0;

    for (int i = 0; i < size; ++i) {
        sum += a[i];
    }

    return sum;
}

void swap_arr(int *a, int *b, int size) {
    for (int i = 0; i < size; i++) {
        int tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

void sort(int **arr, int n, int m) {
    for (int i = 0; i < n; ++i) {
        int min_sum = get_sum(arr[i], n);
        int min_index = i;
        for (int j = i; j < n; ++j) {
            int sum = get_sum(arr[j], m);
            if (min_sum > sum) {
                min_sum = sum;
                min_index = j;
            }
        }
        swap_arr(arr[i], arr[min_index], m);
    }
}

void free_matrix(int **arr, int code, int n) {
    if (code == 3) {
        free(arr[0]);
        free(arr);
    } else if (code == 2) {
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
        *code > 0 && *code < 4) {
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
        if (code == 1) {
            int *ptr = (int*) (res + n);
            for (int i = 0; i < n; ++i) {
                res[i] = ptr + m * i;
            }
        } else if (code == 2) {
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
        } else if (code == 3) {
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
