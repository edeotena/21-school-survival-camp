#include <stdio.h>
#include <stdlib.h>

#define N 15
#define M 13

void make_picture(int **picture, int n, int m);
void transform(int *buf, int **matr, int n, int m, int direction, int len);
void reset_picture(int **picture, int n, int m);
void output(int **picture, int n, int m);

int main() {
    int *picture[N], code_error = 0;
    for (int i = 0; i < N && code_error == 0; ++i) {
        picture[i] = (int*) malloc(M * sizeof(int));
        if (picture[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(picture[i]);
            }
            code_error = 1;
        }
    }

    if (code_error == 0) {
        make_picture(picture, N, M);
        for (int i = 0; i < N; ++i) {
            free(picture[i]);
        }
    }

    return 0;
}

void output(int **picture, int n, int m) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            printf("%d ", picture[i][j]);
        }
        printf("%d", picture[i][m - 1]);
        printf("\n");
    }

    for (int i = 0; i < m - 1; ++i) {
        printf("%d ", picture[n - 1][i]);
    }

    printf("%d", picture[n - 1][m - 1]);
}   

void make_picture(int **picture, int n, int m) {
    int frame_w[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int frame_h[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int tree_trunk[] = { 7, 7, 7, 7 };
    int tree_foliage[] = { 3, 3, 3, 3 };
    int sun_data[6][5] = { { 0, 6, 6, 6, 6 },
                          { 0, 0, 6, 6, 6 },
                          { 0, 0, 6, 6, 6 },
                          { 0, 6, 0, 0, 6 },
                          { 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0 } };

    reset_picture(picture, n, m);

    int sun_size = sizeof(sun_data) / sizeof(sun_data[0]);
    int foliage_size = sizeof(tree_foliage) / sizeof(tree_foliage[0]); 
    int trunk_size = sizeof(tree_trunk) / sizeof(tree_trunk[0]); 
    int frame_len_h = sizeof(frame_h) / sizeof(frame_h[0]);
    int frame_len_w = sizeof(frame_w) / sizeof(frame_w[0]);

    for (int i = 0; i < 6; ++i) {
        transform(sun_data[i], picture, i + 1, N / 2, 1, sun_size);
    }

    transform(tree_foliage, picture, 3, 2, 1, foliage_size);
    transform(tree_foliage, picture, 4, 2, 1, foliage_size);
    transform(tree_foliage, picture, 2, 3, 0, foliage_size);
    transform(tree_foliage, picture, 2, 4, 0, foliage_size);

    transform(tree_trunk, picture, 10, 2, 1, trunk_size);
    transform(tree_trunk, picture, 6, 3, 0, trunk_size);
    transform(tree_trunk, picture, 6, 4, 0, trunk_size);

    transform(frame_w, picture, 0, 0, 1, frame_len_w);
    transform(frame_w, picture, N - 1, 0, 1, frame_len_w);
    transform(frame_w, picture, N / 2, 0, 1, frame_len_w);

    transform(frame_h, picture, 0, 0, 0, frame_len_h);
    transform(frame_h, picture, 0, M / 2, 0, frame_len_h);
    transform(frame_h, picture, 0, M - 1, 0, frame_len_h);

    output(picture, n, m);
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
             picture[i][j] = 0;
        }
    }
}

void transform(int *buf, int **matr, int n, int m, int direction, int len) {
    if (direction == 1) {
        for (int i = 0; i < len; ++i) {
            matr[n][m + i] = buf[i];
        }
    } else {
        for (int i = 0; i < len; ++i) {
            matr[n + i][m] = buf[i];
        }
    }
}
