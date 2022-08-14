#include <math.h>
#include <stdio.h>

#define ERROR 1
#define EPS 1e-6

double calculations(double x) {
    double res = 7e-3 * pow(x, 4);
    res += ((22.8 * pow(x, 1 / 3) - 1e3) * x + 3) / (x * x / 2);
    res -= x * pow(10 + x, 2 / x) + 1.01;
    return res;
}

int main() {
    double a;

    if (scanf("%lf", &a) != 1 || getchar() != '\n') {
        printf("n/a\n");
        return ERROR;
    }

    if (a < EPS && a > -EPS) {
        printf("n/a\n");
        return ERROR;
    }

    printf("%.1lf\n", calculations(a));

    return 0;
}
