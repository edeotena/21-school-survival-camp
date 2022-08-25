#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct my_struct {
    int y, m, d, h, min, s, status, code;
} record;

void remove_end_line(char *str, size_t *len);
int validate(const char *date, size_t len);
int get_file_size_in_bytes(FILE *file);
record read_record_from_file(FILE *file, int index);
void print_record(const record *rec);
int is_in(int yt, int mt, int dt, int y1, int m1, int d1, int y2, int m2, int d2);
void print(FILE *file);
void handle(char *date, char* date2, FILE *file, size_t len, char* file_name);

int main() {
    char *file_name = NULL;
    size_t cap, len = getline(&file_name, &cap, stdin);
    if (file_name != NULL) {
        remove_end_line(file_name, &len);
        --len;
        FILE *file = fopen(file_name, "rb");
        if (file != NULL && get_file_size_in_bytes(file) / sizeof(record) > 0) {
            char *date = NULL;
            size_t cap_date, len_date = getline(&date, &cap_date, stdin);
            if (date != NULL) {
                remove_end_line(date, &len_date);
                --len_date;
                if (validate(date, len_date) == 1) {
                    char *date2 = NULL;
                    size_t cap_date2, len_date2 = getline(&date2, &cap_date2, stdin);
                    if (date2 != NULL) {
                        remove_end_line(date2, &len_date2);
                        --len_date2;
                        if (validate(date2, len_date2) == 1) {
                            handle(date, date2, file, len, file_name);
                        } else {
                            printf("n/a");
                        }
                    } else {
                        printf("n/a");
                    }
                    free(date2);
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

void handle(char *date, char* date2, FILE *file, size_t len, char* file_name) {
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
               (date[8] - '0') * 10 + (date[9] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int year2 = (date2[6] - '0') * 1000 + (date2[7] - '0') * 100 +
                (date2[8] - '0') * 10 + (date2[9] - '0');
    int month2 = (date2[3] - '0') * 10 + (date2[4] - '0');
    int day2 = (date2[0] - '0') * 10 + (date2[1] - '0');
    size_t rec_count = get_file_size_in_bytes(file) / sizeof(record);
    char *temp = (char *) calloc (len + 1, sizeof(char));
    strcat(temp, file_name);
    strcat(temp, "~");
    FILE *copy = fopen(temp, "a+b");
    for (size_t i = 0; i < rec_count; ++i) {
        record rec = read_record_from_file(file, i);
        if (is_in(rec.y, rec.m, rec.d, year, month, day, year2, month2, day2) == 0) {
            fwrite(&rec, sizeof(record), 1, copy);
        }
    }
    free(temp);
    fclose(copy);
    fclose(file);
    rename(temp, file_name);
    file = fopen(file_name, "rb");
    print(file);
}

void print_record(const record *rec) {
    printf("%d %d %d %d %d %d %d %d", rec->y, rec->m, rec->d,
           rec->h, rec->min, rec->s, rec->status, rec->code);
}

void remove_end_line(char *str, size_t *len) {
    if (*len > 0 && str[*len - 1] == '\n') {
        str[*len - 1] = '\0';
        --(*len);
    }
}

int validate(const char *date, size_t len) {
    int res = 1;
    if (len == 9) {
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

int is_in(int yt, int mt, int dt, int y1, int m1, int d1, int y2, int m2, int d2) {
    size_t vt = yt * 10000 + mt * 100 + dt;
    size_t v1 = y1 * 10000 + m1 * 100 + d1;
    size_t v2 = y2 * 10000 + m2 * 100 + d2;
    return v1 <= vt && vt <= v2;
}

void print(FILE *file) {
    size_t rec_size = get_file_size_in_bytes(file) / sizeof(record);

    for (size_t i = 0; i + 1 < rec_size; ++i) {
        record rec = read_record_from_file(file, i);
        print_record(&rec);
        printf("\n");
    }

    if (rec_size != 0) {
        record rec = read_record_from_file(file, rec_size - 1);
        print_record(&rec);
    }
}
