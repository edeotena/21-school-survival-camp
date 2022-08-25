#include <stdio.h>
#include <stdlib.h>

typedef struct my_struct {
    int y, m, d, h, min, s, status, code;
} record;

void remove_end_line(char *str, size_t *len);
int validate(const char *date, size_t len);
int get_file_size_in_bytes(FILE *file);
record read_record_from_file(FILE *file, int index);
void handle(char *date, FILE *file);

int main() {
    char *file_name = NULL;
    size_t cap, len = getline(&file_name, &cap, stdin);
    if (file_name != NULL) {
        remove_end_line(file_name, &len);
        FILE *file = fopen(file_name, "rb");
        if (file != NULL) {
            char *date = NULL;
            size_t cap_date, len_date = getline(&date, &cap_date, stdin);
            if (date != NULL) {
                remove_end_line(file_name, &len_date);
                if (validate(date, len_date) == 1) {
                    handle(date, file);
                } else {
                    printf("n/a");
                }
                free(date);
            } else {
                printf("n/a");
            }
            fclose(file);
        } else {
            printf("n/a");
        }
        free(file_name);
    } else {
        printf("n/a");
    }
    return 0;
}

void handle(char *date, FILE *file) {
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
               (date[8] - '0') * 10 + (date[9] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int day = (date[0] - '0') * 10 + (date[1] - '0');
    size_t rec_count = get_file_size_in_bytes(file) / sizeof(record);
    int found = 0;
    for (size_t i = 0; i < rec_count && found == 0; ++i) {
        record rec = read_record_from_file(file, i);
        if (rec.y == year && rec.m == month && rec.d == day) {
            found = 1;
            printf("%d", rec.code);
        }
    }
    if (found == 0) {
        printf("n/a");
    }
}

void remove_end_line(char *str, size_t *len) {
    if (*len > 0 && str[*len - 1] == '\n') {
        str[*len - 1] = '\0';
        --(*len);
    }
}

int validate(const char *date, size_t len) {
    int res = 1;
    if (len != 10) {
        if (date[2] != '.' || date[5] != '.') {
            res = 0;
        }

        for (size_t i = 0; i < 2; ++i) {
            if (date[i] > '9' || date[i] < '0') {
                res = 0;
            }
        }

        for (size_t i = 3; i < 5; ++i) {
            if (date[i] > '9' || date[i] < '0') {
                res = 0;
            }
        }

        for (size_t i = 6; i < 10; ++i) {
            if (date[i] > '9' || date[i] < '0') {
                res = 0;
            }
        }
    } else {
        res = 0;
    }

    return res;
}

int get_file_size_in_bytes(FILE *file) {
    int size = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    return size;
}

record read_record_from_file(FILE *file, int index) {
    int offset = index * sizeof(record);
    fseek(file, offset, SEEK_SET);

    record rec;
    fread(&rec, sizeof(record), 1, file);
    rewind(file);

    return rec;
}
