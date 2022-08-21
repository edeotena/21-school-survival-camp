#include "structs.h"
#include "parse.h"
#include "polish_notation.h"
#include "draw.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *input = NULL;
    size_t cap = 0;

    getline(&input, &cap, stdin);
    queue *lexems = parse_to_lex(input);
    free(input);

    if (lexems != NULL) {
        queue *lexems_rpn = make_rpn(lexems);
        free_queue(&lexems);

        if (lexems_rpn != NULL) {
            double *coords = get_values(lexems_rpn, 0, 4 * M_PI, 80);
            if (coords != NULL) {
                print_graph(coords, 1, -1, 80, 25);
                free(coords);
            } else {
                printf("n/a");
            }
            free_queue(&lexems_rpn);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }

    return 0;
}
