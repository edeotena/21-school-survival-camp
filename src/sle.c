#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-6

double** input(int *n, int *m);
void free_matrix(double **arr, int n);
int sle(double **matrix, int n, double *roots);
void output_roots(double *roots, int n);
double** new_matrix(int n, int m);

int main() {
    double **matrix;
    int n, m;
    matrix = input(&n, &m);
    if (matrix != NULL) {
        if (n + 1 != m) {
            printf("n/a");
        } else {
            double *res = (double*) malloc(n * sizeof(double));
            if (res != NULL) {
                if (sle(matrix, n, res) == 0) {
                    output_roots(res, n);
                } else {
                    printf("n/a");
                }
                free(res);
            } else {
                printf("n/a");
            }
        }
        free_matrix(matrix, n);
    } else {
        printf("n/a");
    }

    return 0;
}

int sle(double **matrix, int n, double *roots) {
    int code_error = 0;
    double **clone = new_matrix(n, n + 1);
    if (clone != NULL) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n + 1; ++j) {
                clone[i][j] = matrix[i][j];
            }
        }

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n + 1; ++i) {
                clone[k][i] = clone[k][i] / matrix[k][k];
            }
            for (int i = k + 1; i < n; ++i) {
                double K = clone[i][k] / clone[k][k];
                for (int j = 0; j < n + 1; j++) {
                    clone[i][j] = clone[i][j] - clone[k][j] * K;
                }
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n + 1; ++j) {
                    matrix[i][j] = clone[i][j];
                }
            }
        }

        for (int k = n - 1; k > -1; --k) {
            for (int i = n; i > -1; --i) {
                clone[k][i] = clone[k][i] / matrix[k][k];
            }
            for (int i = k - 1; i > -1; --i) {
                double K = clone[i][k] / clone[k][k];
                for (int j = n; j > -1; --j) {
                    clone[i][j] = clone[i][j] - clone[k][j] * K;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            roots[i] = clone[i][n];
        }
        free_matrix(clone, n);
    } else {
        code_error = 1;
    }

    return code_error;
}

double** new_matrix(int n, int m) {
    double **result_matrix = (double**) malloc(n * sizeof(double*));

    if (result_matrix != NULL) {
        int code_error = 0;
        for (int i = 0; i < n && code_error == 0; ++i) {
            result_matrix[i] = (double*) malloc(m * sizeof(double));
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

void free_matrix(double **arr, int n) {
    for (int i = 0; i < n; ++i) {
        free(arr[i]);
    }

    free(arr);

    return;
}

void output_roots(double *roots, int n) {
    for (int i = 0; i < n - 1; ++i) {
        printf("%.6lf ", roots[i]);
    }
    printf("%.6lf ", roots[n - 1]);

    return;
}

double** input(int *n, int *m)  {
    char sym = 0, sc = scanf("%d %d%c", n, m, &sym), code_error = 0;
    double** res = NULL;

    if (!((sc == 2 && sym == 0) || (sc == 3 && sym == '\n')) || *n <= 0 ||
        *m <= 0 || *n + 1 != *m) {
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


