// Copyright 2022 guinicyb@student.21-school.ru

#include <stdio.h>

void maxmin(int prob1, int prob2, int prob3, int *max, int *min);

int main() {
    int x, y, z;
    char sym;

    int sc = scanf("%d %d %d%c", &x, &y, &z, &sym);
    if (!((sc == 3 && !sym) || (sc == 4 && sym == '\n'))) {
        printf("n/a");
        return 0;
    }

    int max, min;

    maxmin(x, y, z, &max, &min);

    printf("%d %d", max, min);

    return 0;
}

void maxmin(int prob1, int prob2, int prob3, int *max, int *min) {
    *max = prob1;
    *min = prob1;

    if (prob2 > *max) *max = prob2;
    if (prob2 < *min) *min = prob2;

    if (prob3 > *max) *max = prob3;
    if (prob3 < *min) *min = prob3;
}
