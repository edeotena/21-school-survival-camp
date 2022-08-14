// Copyright 2022 guinicyb@student.21-school.ru

#include <math.h>
#include <stdio.h>

int divide(int n, int d, int *res, int *rem) {
    if (d == 0) {
        return 1;
    }

    int neg_n = 0, neg_d = 0;
    if (d < 0) {
        d = -d;
        neg_d = 1;
    }

    if (n < 0) {
        n = -n;
        neg_n = 1;
    }

    *res = 0;
    while (n >= d) {
        n -= d;
        ++*res;
    }
    *rem = n;

    if (neg_d == 1) {
         *res = -*res;
    }

    if (neg_n == 1) {
         *res = -*res;
         *rem = -*rem;
    }

    return 0;
}

int abs(int a) {
    if (a < 0) {
         return -a;
    }
    return a;
}

int main() {
    int num;
    if (scanf("%d", &num) != 1 || getchar() != '\n' || num == 0) {
        printf("n/a");
        return 0;
    }

    int max_prime_divisior = 1;

    int div, res;

    divide(num, 2, &div, &res);
    while (res == 0) {
        max_prime_divisior = 2;
        num = div;
        divide(num, 2, &div, &res);
    }

    divide(num, 3, &div, &res);
    while (res == 0) {
        max_prime_divisior = 3;
        num = div;
        divide(num, 3, &div, &res);
    }

    for (int i = 5; i * i <= abs(num); i += 6) {
        divide(num, i, &div, &res);
        while (res == 0) {
            max_prime_divisior = i;
            num = div;
            divide(num, i, &div, &res);
        }
    }

    if (abs(num) > 4) {
        max_prime_divisior = abs(num);
    }

    printf("%d", max_prime_divisior);
    return 0;
}
