#include "draw.h"
#include "polish_notation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double *get_values(queue* func, double left, double right, int steps) {
    double step = (right - left) / (steps - 1);
    double x = left;
    double *res = (double *) calloc(steps, sizeof(double));
    int code = 0;
    if (res == NULL) {
        code = ERROR;
    }

    for (int i = 0; i < steps && code == 0; ++i) {
        double temp = calculate(func, x, &code);
        if (code == 0) {
            res[i] = temp;
            x += step;
        }
    }

    if (code != 0) {
        free(res);
        res = NULL;
    }

    return res;
}

char **create_matrix(int n, int m) {
    char **res = (char **) calloc(n, sizeof(char*));
    if (res != NULL) {
        int code = 0;
        for (int i = 0; i < n && code == 0; ++i) {
            res[i] = (char *) calloc (m, sizeof(char));
            if (res[i] == NULL) {
                for (int j = 0; j < i; ++j) {
                    free(res[j]);
                    res = NULL;
                    code = ERROR;
                }
                free(res);
            }
        }
    }

    return res;
}

int find_closest(double y, double up, double down, int step) {
    int index = -1;
    double min = up;
    double temp = down - (up - down) / (step - 1);
    for (int i = -1; i < step + 1; ++i) {
        if (fabs(y - temp) < min) {
            min = fabs(y - temp);
            index = i;
        }
        temp += (up - down) / (step - 1);
    }
    return index;
}

void print_graph(const double *coords, double up, double down,  int steps_x, int steps_y) {
    char **field = create_matrix(steps_x, steps_y);
    if (field != NULL) {
        double closest = (up - down) / steps_y;
        for (int i = 0; i < steps_x; ++i) {
            double y = down;
            int index = find_closest(coords[i], up, down, steps_y);
            for (int j = 0; j < steps_y; ++j) {
                if (j == index) {
                    field[i][j] = '*';
                } else {
                    field[i][j] = '.';
                }
                y += closest;
            }
        }

        for (int i = 0; i < steps_y; ++i) {
            for (int j = 0; j < steps_x; ++j) {
                printf("%c", field[j][i]);
            }
            if (i != steps_x - 1) {
                printf("\n");
            }
        }

        for (int j = 0; j < steps_x; ++j) {
            free(field[j]);
        }
        free(field);
    } else {
        printf("n/a");
    }
}
