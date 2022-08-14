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

double double_abs(double a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

int main() {
    double max_ag = 0, max_be = 0, max_hy = 0;
    double min_ag = 0, min_be = 0, min_hy = 0;
    for (double i = -M_PI; i <= M_PI; i += STEP) {
        double ag = agnesi(i), be = bernoulli(i), hy = hyperbola(i);

        if (max_ag < ag) {
            max_ag = ag;
        }
        if (max_ag > ag) {
            min_ag = ag;
        }

        if (sqrt(1 + 4 * i * i) - i * i - 1 >= EPS) {
            if (max_be < be) {
                max_be = be;
            }
            if (min_be > be) {
                min_be = be;
            }
        }

        if (i <= -EPS || i >= EPS) {
            if (max_hy < hy) {
                max_hy = hy;
            }
            if (min_hy > hy) {
                min_hy = hy;
            }
        }
    }

    double delta_ag = (max_ag - min_ag) / 20;
    for (double i = -M_PI; i <= M_PI; i += STEP) {
        double closest = double_abs(agnesi(i) - min_ag), closest_index = min_ag;
        for (double j = min_ag; j <= max_ag; j += delta_ag) {
            if (double_abs(agnesi(i) - j) < closest) {
                closest = double_abs(agnesi(i) - j);
                closest_index = j;
            }
        }
        for (double j = min_ag; j <= max_ag; j += delta_ag) {
            if (double_abs(closest_index - j) <= EPS) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    double delta_be = (max_be - min_be) / 20;
    for (double i = -M_PI; i <= M_PI; i += STEP) {
        if (sqrt(1 + 4 * i * i) - i * i - 1 < EPS) {
            printf("\n");
            continue;
        }
        double closest = double_abs(bernoulli(i) - min_be);
        double closest_index = min_be;
        for (double j = min_be; j <= max_be; j += delta_be) {
            if (double_abs(bernoulli(i) - j) < closest) {
                closest = double_abs(bernoulli(i) - j);
                closest_index = j;
            }
        }
        for (double j = min_be; j <= max_be; j += delta_be) {
            if (double_abs(closest_index - j) <= EPS) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    double delta_hy = (max_hy - min_hy) / 20;
    for (double i = -M_PI; i <= M_PI; i += STEP) {
        double closest = double_abs(hyperbola(i) - min_hy);
        double closest_index = min_hy;
        for (double j = min_hy; j <= max_hy; j += delta_hy) {
            if (double_abs(hyperbola(i) - j) < closest) {
                closest = double_abs(hyperbola(i) - j);
                closest_index = j;
            }
        }
        for (double j = min_hy; j <= max_hy; j += delta_hy) {
            if (double_abs(closest_index - j) <= EPS) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
