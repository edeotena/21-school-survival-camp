#include "print_module.h"
#include "documentation_module.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    print_log(print_char, Module_load_success_message);

    int *availability_mask = check_available_documentation_module(validate, Documents_count, Documents);
    if (availability_mask != NULL) {
        char *arr[] = {Documents};
        for (int i = 0; i < Documents_count - 1; ++i) {
            printf("%-15s: %savailable\n", arr[i], (availability_mask[i] == 0 ? "un" : ""));
        }
        printf("%-15s: %savailable", arr[Documents_count - 1],
                (availability_mask[Documents_count - 1] == 0 ? "un" : ""));
        free(availability_mask);
    } else {
        printf("n/a");
    }

    return 0;
}
