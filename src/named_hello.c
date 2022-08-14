#include <stdio.h>

#define ERROR 1

int main() {
    int name;
    if (scanf("%d", &name) != 1 || getchar() != '\n') {
        printf("n/a\n");
        return ERROR;
    }
    printf("Hello, %d!\n", name);
    return 0;
}
