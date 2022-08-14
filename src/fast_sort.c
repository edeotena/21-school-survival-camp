// Copyright 2022 guinicyb@student.21-school.ru

#include <stdio.h>
#define NMAX 10
#define ERROR -1

int input(int *a);
void output(int *a);
void quicksort(int* a, int lt, int rh);
void swap(int *a, int *b);
void heapify(int *a, int n, int i);
void heap_sort(int *a);
void copy_data(int *a, int *b);
void output_error();
void next_line();

int main() {
    int data[NMAX], code = 0;
    if (input(data) != 0) {
        output_error();
        code = ERROR;
    }

    if (code == 0) {
        int data_copy[NMAX];
        copy_data(data, data_copy);

        quicksort(data, 0, NMAX);
        output(data);
        next_line();

        heap_sort(data_copy);
        output(data_copy);
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

    if (code == 0) {
        char sym;
        int sc = scanf("%d%c", p, &sym);

        if (!((sc == 1 && !sym) || (sc == 2 && sym == '\n'))) {
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

void quicksort(int* a, int lt, int rh) {
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

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;

    return;
}

void heapify(int* a, int n, int i) {
    int largest = i;
    int lt = 2 * i + 1;
    int rh = 2 * i + 2;

    if (lt < n && *(a + lt) > *(a + largest)) {
        largest = lt;
    }

    if (rh < n && *(a + rh) > *(a + largest)) {
        largest = rh;
    }

    if (largest != i) {
        swap(a + i, a + largest);
        heapify(a, n, largest);
    }

    return;
}

void heap_sort(int* a) {
    for (int i = NMAX / 2 - 1; i >= 0; i--) {
        heapify(a, NMAX, i);
    }

    for (int i = NMAX - 1; i >= 0; i--) {
        swap(a, a + i);

        heapify(a, i, 0);
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

void next_line() {
    printf("\n");

    return;
}
