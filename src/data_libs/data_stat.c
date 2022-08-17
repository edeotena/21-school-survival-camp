#include "data_stat.h"
#include <stdlib.h>

double max(const double *data, int n) {
    double max_num = data[0];
    for (int i = 1; i < n; ++i) {
        if (data[i] > max_num) {
            max_num = data[i];
        }
    }
    return max_num;
}

double min(const double *data, int n) {
    double min_num = data[0];
    for (int i = 1; i < n; ++i) {
        if (data[i] < min_num) {
            min_num = data[i];
        }
    }
    return min_num;
}

double mean(double *data, int n) {
    double mean = 0;

    for (double *p = data; p - data < n; ++p) {
        mean += *p;
    }

    return mean / n;
}

double variance(double *data, int n) {
    double res = 0;
    double mn = mean(data, n);

    for (double *p = data; p - data < n; ++p) {
        res += (*p - mn) * (*p - mn);
    }

    return res;
}
