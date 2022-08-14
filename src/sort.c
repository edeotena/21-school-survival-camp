// Copyright 2022 guinicyb@student.21-school.ru

#include <stdio.h>
#define NMAX 10
#define ERROR -1

int input(int *a);
void output(int *a);
void sort(int *a);
void output_error();

int main() {
    int data[NMAX];

    if (input(data) != 0) {
        output_error();
    } else {
        sort(data);

        output(data);
    }

    return 0;
}

int input(int *a) {
    int *p = a, code = 0;
    for (; p - a < NMAX - 1 && code == 0; ++p) {
        if (code == 0 && scanf("%d", p) != 1) {
            code = ERROR;
        }
    }
    if (code != ERROR) {
        char sym;
        int sc = scanf("%d%c", p, &sym);
        if ((sc == 1 && !sym) || (sc == 2 && sym == '\n')) {
            code = 0;
        } else {
            code = ERROR;
        }
    }

    return code;
}

void output(int *a) {
    int *p = a;

    for (; p - a < NMAX - 1; ++p) {
        printf("%d ", *p);
    }

    printf("%d", *p);

    return;
}

void sort(int *a) {
    for (int *p = a; p - a < NMAX - 1; ++p) {
        for (int *p2 = a; p2 - a < NMAX - 1; ++p2) {
            if (*p2 > *(p2 + 1)) {
                int tmp = *(p2 + 1);
                *(p2 + 1) = *p2;
                *p2 = tmp;
            }
        }
    }
    return;
}

void output_error() {
    printf("n/a");

    return;
}
