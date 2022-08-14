#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int **matrix, int n, int m, int** result_matrix);
void sort_horizontal(int **matrix, int n, int m, int **result_matrix);

int** input(int *n, int *m);
void free_matrix(int **arr, int n);
void output(int **matrix, int n, int m);
void get_smallest_idxs(int **matrix, int n, int m, int* i_sm, int* j_sm, int i_st, int j_st);
void sort_matrix(int **matrix, int n, int m);
int** new_matrix(int n, int m);

int main() {
    int **matrix;
    int n, m;

    matrix = input(&n, &m);
    if (matrix != NULL) {
        sort_matrix(matrix, n, m);
        int** res = new_matrix(n, m);
        if (res != NULL) {
            sort_vertical(matrix, n, m, res);
            output(res, n, m);
            printf("\n\n");
            sort_horizontal(matrix, n, m, res);
            output(res, n, m);
            free_matrix(res, n);
        }
        free_matrix(matrix, n);
    } else {
        printf("n/a");
    }

    return 0;
}

int** new_matrix(int n, int m) {
    int **result_matrix = (int**) malloc(n * sizeof(int*));

    if (result_matrix != NULL) {
        int code_error = 0;
        for (int i = 0; i < n && code_error == 0; ++i) {
            result_matrix[i] = (int*) malloc(m * sizeof(int));
            if (result_matrix[i] == NULL) {
                code_error = 1;
                for (int j = 0; j <= i; ++j) {
                    free(result_matrix[i]);
                }
                free(result_matrix);
            }
        }
    }

    return result_matrix;
}

void sort_vertical(int **matrix, int n, int m, int** result_matrix) {
    int pos_i = 0, pos_j = 0, pos_i_s = 0, pos_j_s = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result_matrix[pos_i][pos_j] = matrix[i][j];
            if (pos_i == 0 && pos_j % 2 == 0) {
                pos_i_s = 1;
                pos_j_s = 0;
            } else if (pos_i == n - 1 && pos_j % 2 == 0) {
                pos_i_s = 0;
                pos_j_s = 1;
            } else if (pos_i == n - 1 && pos_j % 2 == 1) {
                pos_i_s = -1;
                pos_j_s = 0;
            } else if (pos_i == 0 && pos_j % 2 == 1) {
                pos_i_s = 0;
                pos_j_s = 1;
            }
            pos_i += pos_i_s;
            pos_j += pos_j_s;
        }
    }
}

void sort_horizontal(int **matrix, int n, int m, int** result_matrix) {
    int start = 0;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; ++j) {
                result_matrix[start / m][start % m] = matrix[i][j];
                start += 1;
            }
        } else {
            for (int j = m - 1; j >= 0; --j) {
                result_matrix[start / m][start % m] = matrix[i][j];
                start += 1;
            }
        }
    }
}

void get_smallest_idxs(int **matrix, int n, int m, int* i_sm, int* j_sm, int i_st, int j_st) {
    int smallest = matrix[i_st][j_st];
    *i_sm = i_st;
    *j_sm = j_st;
    for (int i = i_st; i < n; ++i) {
        for (int j = (i == i_st ? j_st : 0); j < m; ++j) {
            if (matrix[i][j] < smallest) {
                smallest = matrix[i][j];
                *i_sm = i, *j_sm = j;
            }
        }
    }
}

void sort_matrix(int **matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int i_sm, j_sm;
            get_smallest_idxs(matrix, n, m, &i_sm, &j_sm, i, j);
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[i_sm][j_sm];
            matrix[i_sm][j_sm] = tmp;
        }
    }
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
        code_error = 1;
    }

    if (code_error == 0) {
        res = (int**) malloc(*n * sizeof(int*));

        if (res != NULL) {
            for (int i = 0; i < *n && code_error == 0; ++i) {
                res[i] = (int*) malloc(*m * sizeof(int));
                if (res[i] == NULL) {
                    code_error = 1;
                    for (int j = 0; j <= i; ++j) {
                        free(res[i]);
                    }
                    free(res);
                }
            }

            if (code_error == 0) {
                for (int i = 0; i < *n && code_error == 0; ++i) {
                    for (int j = 0; j < *m - 1 && code_error == 0; ++j) {
                        if (scanf("%d", &res[i][j]) != 1) {
                            code_error = 1;
                            free_matrix(res, *n);
                            res = NULL;
                        }
                    }

                    if (code_error == 0) {
                        sym = 0, sc = scanf("%d%c", &res[i][*m - 1], &sym);
                        if (!((sc == 1 && sym == 0) || (sc == 2 && sym == '\n'))) {
                            code_error = 1;
                            free_matrix(res, *n);
                            res = NULL;
                        }
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
