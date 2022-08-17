#include "data_process.h"
#include <data_io.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    double *data;
    int n;

    data = input(&n);

    if (data != NULL) {
        if (n > 0 && normalization(data, n)) {
            output(data, n);
        } else {
            printf("ERROR");
        }
        free(data);
    } else {
        printf("n/a");
    }
    return 0;
}
