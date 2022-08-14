#include <stdio.h>

#define ERROR 1

int main() {
    double x, y;
    if (scanf("%lf%lf", &x, &y) != 2 || getchar() != '\n') {
        printf("n/a\n");
        return ERROR;
    }

    if (x * x + y * y < 25) {
        printf("GOTCHA\n");
    } else {
        printf("MISS\n");
    }

    return 0;
}
