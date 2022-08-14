#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

int** input(int *n, int *m);
void output(int **matrix, int n, int m);
void free_matrix(int **arr, int n);
int **sum(int **matrix_first, int n_first, int m_first, int **matrix_second,
    int n_second, int m_second, int *n_result, int *m_result);
int** transpose(int **matrix, int n, int m);
int** mul(int **matrix_first, int n_first, int m_first, int **matrix_second,
    int n_second, int m_second, int *n_result, int *m_result);

int main() {
    int code = 0;
    char sym = 0, sc = scanf("%d%c", &code, &sym);
    if (((sc == 1 && sym == 0) || (sc == 2 && sym == '\n')) &&
        code > 0 && code < 4) {
        int n, m, **matrix = input(&n, &m);
        if (matrix != NULL) {
            if (code == 3) {
                int n_res = m, m_res = n, **trans_matrix = transpose(matrix, n, m);
                if (trans_matrix != NULL) {
                    output(trans_matrix, n_res, m_res);
                    free_matrix(trans_matrix, n_res);
                } else {
                    printf("n/a");
                }
            } else {
                int n2, m2, **matrix2 = input(&n2, &m2);
                if (matrix2 != NULL) {
                    int res_n, res_m, **res_matrix;
                    if (code == 1) {
                        res_matrix = sum(matrix, n, m, matrix2, n2, m2, &res_n, &res_m);
                    } else {
                        res_matrix = mul(matrix, n, m, matrix2, n2, m2, &res_n, &res_m);
                    }
                    if (res_matrix != NULL) {
                        output(res_matrix, res_n, res_m);
                        free_matrix(res_matrix, res_n);
                    } else {
                        printf("n/a");
                    }
                    free_matrix(matrix2, n2);
                } else {
                    printf("n/a");
                }
            }
            free_matrix(matrix, n);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }

    return 0;
}

void free_matrix(int **arr, int n) {
    for (int i = 0; i < n; ++i) {
        free(arr[i]);
    }

    free(arr);

    return;
}

int** input(int *n, int *m)  {
    char sym = 0, sc = scanf("%d %d%c", n, m, &sym), code_error = 0;
    int** res = NULL;

    if (!((sc == 2 && sym == 0) || (sc == 3 && sym == '\n')) || *n <= 0 ||
        *m <= 0) {
        code_error = ERROR;
    }

    if (code_error == 0) {
        res = (int**) malloc(*n * sizeof(int*));

        if (res != NULL) {
            for (int i = 0; i < *n && code_error == 0; ++i) {
                res[i] = (int*) malloc(*m * sizeof(int));
                if (res[i] == NULL) {
                    code_error = ERROR;
                    for (int j = 0; j <= i; ++j) {
                        free(res[i]);
                    }
                    free(res);
                }
            }
        }

        if (code_error == 0) {
            for (int i = 0; i < *n && code_error == 0; ++i) {
               for (int j = 0; j < *m - 1 && code_error == 0; ++j) {
                    if (scanf("%d", &res[i][j]) != 1) {
                        code_error = ERROR;
                        free_matrix(res, *n);
                        res = NULL;
                    }
                }

                if (code_error == 0) {
                    sym = 0, sc = scanf("%d%c", &res[i][*m - 1], &sym);
                    if (!((sc == 1 && sym == 0) || (sc == 2 && sym == '\n'))) {
                        code_error = ERROR;
                        free_matrix(res, *n);
                        res = NULL;
                   }
                }
            }
        }
    }

    return res;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            printf("%d ", matrix[i][j]);
        }

        printf("%d\n", matrix[i][m - 1]);
    }

    for (int j = 0; j < m - 1; ++j) {
        printf("%d ", matrix[n - 1][j]);
    }
    printf("%d", matrix[n - 1][m - 1]);
}

int** sum(int **matrix_first, int n_first, int m_first, int **matrix_second,
    int n_second, int m_second, int *n_result, int *m_result) {
    int **matrix_result = NULL;
    if (n_first == n_second && m_first == m_second) {
        matrix_result = (int**) malloc(n_first * sizeof(int*));
        if (matrix_result != NULL) {
            int code_error = 0;
            for (int i = 0; i < n_first && code_error == 0; ++i) {
                matrix_result[i] = (int*) malloc(m_first * sizeof(int));
                if (matrix_result[i] == NULL) {
                    code_error = ERROR;
                    for (int j = 0; j <= i; ++j) {
                        free(matrix_result[i]);
                    }
                    free(matrix_result);
                }
            }

            if (code_error == 0) {
                *n_result = n_first;
                *m_result = m_first;
                for (int i = 0; i < n_first; ++i) {
                    for (int j = 0; j < m_first; ++j) {
                        matrix_result[i][j] = matrix_first[i][j] + matrix_second[i][j];
                    }
                }
            }
        }
    }

    return matrix_result;
}

int** mul(int **matrix_first, int n_first, int m_first, int **matrix_second,
    int n_second, int m_second, int *n_result, int *m_result) {
    int **matrix_result = NULL;
    if (m_first == n_second) {
        matrix_result = (int**) malloc(n_first * sizeof(int*));
        if (matrix_result != NULL) {
            int code_error = 0;
            for (int i = 0; i < n_first && code_error == 0; ++i) {
                matrix_result[i] = (int*) malloc(m_second * sizeof(int));
                if (matrix_result[i] == NULL) {
                    code_error = ERROR;
                    for (int j = 0; j <= i; ++j) {
                        free(matrix_result[i]);
                    }
                    free(matrix_result);
                }
            }

            if (code_error == 0) {
                *n_result = n_first;
                *m_result = m_second;
                for (int i = 0; i < n_first; ++i) {
                    for (int j = 0; j < m_second; ++j) {
                        int elem = 0;
                        for (int k = 0; k < m_first; ++k) {
                            elem += matrix_first[i][k] * matrix_second[k][j];
                        }
                        matrix_result[i][j] = elem;
                    }
                }
            }
        }
    }

    return matrix_result;
}

int** transpose(int **matrix, int n, int m) {
    int **matrix_result = (int **) malloc (m * sizeof(int*));
    if (matrix_result != NULL) {
        int code_error = 0;
        for (int i = 0; i < m && code_error == 0; ++i) {
             matrix_result[i] = (int*) malloc(n * sizeof(int));
            if (matrix_result[i] == NULL) {
                code_error = ERROR;
                for (int j = 0; j <= i; ++j) {
                    free(matrix_result[i]);
                }
                free(matrix_result);
            }
        }

        if (code_error == 0) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    matrix_result[i][j] = matrix[j][i];
                }
            }
        }
    }

    return matrix_result;
}
