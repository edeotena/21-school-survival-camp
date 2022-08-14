// Copyright 2022 guinicyb@student.21-school.ru

#include <stdio.h>
#define NMAX 10
#define ERROR -1

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) != 0) {
        printf("n/a");
        return 0;
    } else if (n == 0) {
        return 0;
    }

    squaring(data, n);
    output(data, n);

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
    printf("%d", *p);
}

void squaring(int *a, int n) {
    for (int *p = a; p - a < n; ++p) {
        *p = (*p) * (*p);
    }
}
