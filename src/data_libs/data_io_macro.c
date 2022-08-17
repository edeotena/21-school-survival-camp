#include "data_io.h"
#include <stdio.h>
#include <stdlib.h>

void output(const double *arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        printf("%.2lf ", arr[i]);
    }
    printf("%.2lf", arr[size - 1]);
}

double* input(int *size) {
    double *arr = NULL;
    if (scanf("%d", size) == 1 && *size > 0) {
        arr = (double *) malloc(*size * sizeof(double));
        if (arr != NULL) {
            int code_error = 0;
            for (int i = 0; i < *size && code_error == 0; ++i) {
                if (scanf("%lf", &arr[i]) != 1) {
                    code_error = 1;
                    free(arr);
                    arr = NULL;
                }
            }
        }
    }
    return arr;
}

