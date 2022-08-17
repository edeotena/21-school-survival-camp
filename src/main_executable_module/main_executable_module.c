#include <stdio.h>
#include <stdlib.h>
#include "data_process.h"
#include "decision.h"

#ifndef MACRO
#include "data_io.h"
#else
#include "data_io_macro.h"
#endif

#ifdef SHARED
#include <dlfcn.h>
#endif

int main() {
    int library_found = 1;
    #ifdef SHARED
    void* head = dlopen("./libdata_process.so", RTLD_LAZY);
    if (head == NULL) {
        library_found = 0;
    }
    dlclose(head);
    #endif
    if (library_found == 1) {
        double *data;
        int n;
        printf("LOAD DATA...\n");
        data = input(&n);
        if (data != NULL) {
            printf("RAW DATA:\n\t");
            output(data, n);
           int ok;
            printf("\nNORMALIZED DATA:\n\t");
            #ifdef SHARED
            void* head = dlopen("./libdata_process.so", RTLD_LAZY);
            int (*normalization)(double *data, int n) = dlsym(head, "normalization");
            ok = normalization(data, n);
            dlclose(head);
            #else
            ok = normalization(data, n);
            #endif
            if (ok) {
                output(data, n);

                printf("\nSORTED NORMALIZED DATA:\n\t");
                #ifdef SHARED
                void* head = dlopen("./libdata_process.so", RTLD_LAZY);
                void (*quicksort)(double *a, int lt, int rh) = dlsym(head, "quicksort");
                quicksort(data, 0, n - 1);
                dlclose(head);
                #else
                quicksort(data, 0, n - 1);
                #endif
                output(data, n);

                printf("\nFINAL DECISION:\n\t");
                if (make_decision(data, n)) {
                    printf("YES");
                } else {
                    printf("NO");
                }
            } else {
                printf("ERROR");
            }
        free(data);
        } else {
            printf("n/a");
        }
    } else {
        printf("No dynamic lib in directory!");
    }

    return 0;
}
