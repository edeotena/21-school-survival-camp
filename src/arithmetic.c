#include <stdio.h>

#define ERROR 1

int sum(int a, int b) { return a + b; }

int mul(int a, int b) { return a * b; }

int diff(int a, int b) { return a - b; }

int quot(int a, int b) { return a / b; }

int main() {
    int a, b;

    if (scanf("%d%d", &a, &b) != 2 || getchar() != '\n') {
        printf("n/a");
        return ERROR;
    }

    printf("%d %d %d ", sum(a, b), diff(a, b), mul(a, b));

    if (b == 0) {
        printf("n/a\n");
    } else {
        printf("%d\n", quot(a, b));
    }

    return 0;
}
