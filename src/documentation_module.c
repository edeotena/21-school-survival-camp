#include "documentation_module.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

int* check_available_documentation_module(int(*validate) (char*), int document_count, ...) {
    int *res = NULL;
    if (document_count <= 16 && document_count > 0) {
        res = (int *) calloc(document_count , sizeof(int));
        va_list docs;
        va_start(docs, document_count);
        for (int i = 0; i < document_count; ++i) {
            char *str = va_arg(docs, char *);
            res[i] = validate(str);
        }
        va_end(docs);
    }
    return res;
}

int validate(char* data) {
    int validation_result = !strcmp(data, Available_document);
    return validation_result;
}
