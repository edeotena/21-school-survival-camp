// Copyright 2022 guinicyb@student.21-school.ru

#include <stdio.h>
#define NMAX 10
#define ERROR -1

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];

    if (input(data, &n) != 0) {
        printf("n/a");
        return 0;
    } else if (n == 0) {
        return 0;
    }

    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(n));

    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || *n < 0 || *n > NMAX) {
        return ERROR;
    }

    if (*n == 0) {
        return 0;
    }

    int *p = a;
    for (; p - a < *n - 1; ++p) {
        if (scanf("%d", p) != 1) {
            return ERROR;
        }
    }

    char sym;
    int sc = scanf("%d%c", p, &sym);
    if ((sc == 1 && !sym) || (sc == 2 && sym == '\n')) {
        return 0;
    }

    return ERROR;
}

void output(int *a, int n) {
    int *p = a;

    for (; p - a < n - 1; ++p) {
        printf("%d ", *p);
    }

    printf("%d\n", *p);
}

int max(int *a, int n) {
    int max = *a;

    for (int *p = a; p - a < n; ++p) {
        if (max < *p) {
            max = *p;
        }
    }

    return max;
}

int min(int *a, int n) {
    int min = *a;

    for (int *p = a; p - a < n; ++p) {
        if (min > *p) {
            min = *p;
        }
    }

    return min;
}

double mean(int *a, int n) {
    double mean = 0;

    for (int *p = a; p - a < n; ++p) {
        mean += *p;
    }

    return mean / n;
}

double variance(int n) { return (n * n - 1.0) / 12; }

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}
