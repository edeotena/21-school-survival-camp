// Copyright 2022 guinicyb@student.21-school.ru

#include <stdio.h>
#define NMAX 10
#define ERROR -1

int input(int *buffer, int *length, int *shift);
void output(int *buffer, int length);
void shift(int *buffer, int length, int num);
void copy_data(int *a, int *b);
void output_error();

int main() {
    int n, sh, data[NMAX];

    if (input(data, &n, &sh) != 0) {
        output_error();
    } else {
        shift(data, n, sh);

        output(data, n);
    }

    return 0;
}

int input(int *buffer, int *length, int *shift) {
    int code = 0;
    if (scanf("%d", length) != 1 || *length < 0 || *length > NMAX) {
        code = ERROR;
    }

    if (code == 0 && *length != 0) {
        int *p = buffer;
        for (; p - buffer < *length && code == 0; ++p) {
        if (code == 0 && scanf("%d", p) != 1) {
                code = ERROR;
            }
        }

        if (code == 0) {
            char sym;
            int sc = scanf("%d%c", shift, &sym);
            if (!((sc == 1 && !sym) || (sc == 2 && sym == '\n'))) {
                code = ERROR;
            }
        }
    }

    return code;
}

void output(int *buffer, int length) {
    int *p = buffer;
    for (; p - buffer < length - 1; ++p) {
        printf("%d ", *p);
    }

    if (length > 0) {
        printf("%d", *p);
    }

    return;
}

void shift(int *buffer, int length, int num) {
    if (length != 0) {
        num %= length;

        if (num < 0) {
            num = length + num;
        }

        int temp[NMAX];
        copy_data(buffer, temp);

        for (int i = 0; i < length; ++i) {
            buffer[i] = temp[(i + num) % length];
        }
    }

    return;
}

void copy_data(int *a, int *b) {
    for (int *p = a; p - a < NMAX; ++p) {
        *(b + (p - a)) = *p;
    }

    return;
}

void output_error() {
    printf("n/a");

    return;
}
