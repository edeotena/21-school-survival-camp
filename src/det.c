#include <stdio.h>
#include <stdlib.h>

double** input(int *n, int *m);
void free_matrix(double **arr, int n);
void less_double_arr(double **matrix, double **new_matrix, int row, int col, int size);
double get_det(double **matrix, int n);

int main() {
    double **matrix;
    int n, m;

    matrix = input(&n, &m);
    if (matrix != NULL) {
        if (n != m) {
            printf("n/a");
        } else {
            double det = get_det(matrix, n);
            printf("%.6lf", det);
        }
        free_matrix(matrix, n);
    } else {
        printf("n/a");
    }

    return 0;
}

double get_det(double **matrix, int n) {
    int det_power = 1;

    double ret = 0;

    if (n == 1) {
        ret = matrix[0][0];
    } else if (n == 2) {
        ret = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    } else {
        double** matrix_2 = (double**)malloc(sizeof(double) * n);

        for (int i = 0; i < n; ++i) {
            matrix_2[i] = (double*)malloc(sizeof(double) * n);
        }

        for (int i = 0; i < n; ++i) {
            less_double_arr(matrix, matrix_2, i, 0, n);
            ret = ret + det_power * matrix[i][0] * get_det(matrix_2, n - 1);
            det_power = -det_power;
        }
        free_matrix(matrix_2, n);
    }


    return(ret);
}


void less_double_arr(double **matrix, double **new_matrix, int row, int col, int size) {
    int skip_i = 0;
    for (int i = 0; i < size - 1; ++i) {
        if (i == row) {
            skip_i = 1;
        }
        int skip_j = 0;
        for (int j = 0; j < size - 1; ++j) {
            if (j == col) {
                skip_j = 1;
            }
            new_matrix[i][j] = matrix[i + skip_i][j + skip_j];
        }
    }
}

void free_matrix(double **arr, int n) {
    for (int i = 0; i < n; ++i) {
        free(arr[i]);
    }

    free(arr);

    return;
}

double** input(int *n, int *m)  {
    char sym = 0, sc = scanf("%d %d%c", n, m, &sym), code_error = 0;
    double** res = NULL;

    if (!((sc == 2 && sym == 0) || (sc == 3 && sym == '\n')) || *n <= 0 ||
        *m <= 0 || *n != *m) {
        code_error = 1;
    }

    if (code_error == 0) {
        res = (double**) malloc(*n * sizeof(double*));

        if (res != NULL) {
            for (int i = 0; i < *n && code_error == 0; ++i) {
                res[i] = (double*) malloc(*m * sizeof(double));
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
                        if (scanf("%lf", &res[i][j]) != 1) {
                            code_error = 1;
                            free_matrix(res, *n);
                            res = NULL;
                        }
                    }

                    if (code_error == 0) {
                        sym = 0, sc = scanf("%lf%c", &res[i][*m - 1], &sym);
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
