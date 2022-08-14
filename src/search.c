// Copyright 2022 guinicyb@student.21-school.ru

#include <math.h>
#include <stdio.h>

#define NMAX 30
#define ERROR -1

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
int check_num(int num, double mean, double variance);

int main() {
    int n, data[NMAX];
    if (input(data, &n) != 0) {
        printf("n/a");
        return 0;
    } else if (n == 0) {
        return 0;
    }

    int res = 0;
    for (int *p = data; p - data < n; ++p) {
        if (check_num(*p, mean(data, n), variance(data, n)) == 1) {
            res = *p;
            break;
        }
    }

    printf("%d", res);
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

double mean(int *a, int n) {
    double mean = 0;

    for (int *p = a; p - a < n; ++p) {
        mean += *p;
    }

    return mean / n;
}

double variance(int *a, int n) {
    double res = 0;
    double mn = mean(a, n);

    for (int *p = a; p - a < n; ++p) {
        res += (*p - mn) * (*p - mn);
    }

    return res;
}

int check_num(int num, double mean, double variance) {
    if (num % 2 == 0 && num != 0 && num >= mean &&
        num <= mean + 3 * sqrt(variance)) {
        return 1;
    }
    return 0;
}
