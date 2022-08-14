
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

int* input(int *n);
void output(int *a, int n);
void swap(int *a, int *b);
void sort(int *a, int n);

int main() {
    int n, *data = input(&n);
    if (data != NULL) {
        sort(data, n);

        output(data, n);
        free(data);
    } else {
        printf("n/a");
    }

    return 0;
}

int* input(int *n) {
    char first_line;
    int sc = scanf("%d%c", n, &first_line), *res = NULL;

    if (((sc == 1 && first_line) || (sc == 2 &&
        first_line == '\n')) && *n > 0) {
        res = (int *)  malloc(*n * sizeof(int));

        if (res != NULL) {
            int code = 0;
            for (int i = 0; i < *n - 1 && code == 0; ++i) {
                if (scanf("%d", &res[i]) != 1) {
                    free(res);
                    res = NULL;
                    code = ERROR;
                }
            }

            if (code == 0) {
                char sym = 0;
                sc = scanf("%d%c", &res[*n - 1], &sym);
                if (!((sc == 1 && !sym) || (sc == 2 && sym == '\n'))) {
                    free(res);
                    res = NULL;
                }
            }
        }
    }

    return res;
}

void output(int *a, int n) {
    for (int i = 0; i < n - 1; ++i) {
        printf("%d ", a[i]);
    }

    printf("%d", a[n - 1]);

    return;
}

void sort(int *a, int n) {
    for (int *p = a; p - a < n - 1; ++p) {
        for (int *p2 = a; p2 - a < n - 1; ++p2) {
            if (*p2 > *(p2 + 1)) {
                swap(p2, p2 + 1);
            }
        }
    }

    return;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;

    return;
}
