// Copyright 2022 guinicyb@student.21-school.ru

#include <math.h>
#include <stdio.h>

#define STEP 2 * M_PI / 41
#define EPS 1e-6

double agnesi(double x) {
    return 1 / (1 + x * x);
}

double bernoulli(double x) {
    return sqrt(sqrt(1 + 4 * x * x) - x * x - 1);
}

double hyperbola(double x) {
    return 1 / (x * x);
}

int main() {
    for (double i = -M_PI; i <= M_PI; i += STEP) {
        printf("%.7lf | %.7lf | ", i, agnesi(i));

        if (sqrt(1 + 4 * i * i) - i * i - 1 < EPS) {
            printf("- | ");
        } else {
            printf("%.7lf | ", bernoulli(i));
        }

        if (i > -EPS && i < EPS) {
            printf(" -\n");
        } else {
            printf("%.7lf\n", hyperbola(i));
        }
    }
    return 0;
}
