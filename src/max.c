#include <stdio.h>

#define ERROR 1

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int main() {
    int a, b;

    if (scanf("%d%d", &a, &b) != 2 || getchar() != '\n') {
        printf("n/a\n");
        return ERROR;
    }

    printf("%d\n", max(a, b));

    return 0;
}
