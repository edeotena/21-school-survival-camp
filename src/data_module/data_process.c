#include "data_process.h"
#include "data_stat.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int normalization(double *data, int n) {
    int result = 1;
    double max_value = max(data, n);
    double min_value = min(data, n);
    double size = max_value - min_value;

    if (fabs(size) > EPS) {
        for (int i = 0; i < n; i++) {
            data[i] = data[i] / size - min_value / size;
        }
    } else {
        result = 0;
    }

    return result;
}

void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;

    return;
}

void quicksort(double* a, int lt, int rh) {
    if (lt < rh) {
        int i = lt;
        int j = rh;

        while (i < j) {
            while (*(a + i) <= *(a + lt) && i < rh) {
                i++;
            }

            while (*(a + j) > *(a + lt)) {
                j--;
            }

            if (i < j) {
                swap(a + i, a + j);
            }
        }

    swap(a + lt, a + j);

    quicksort(a, lt, j-1);
    quicksort(a, j+1, rh);
    }

    return;
}
