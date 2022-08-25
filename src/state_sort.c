#include <stdio.h>
#include <stdlib.h>

#define ERROR (-1)

typedef struct my_struct {
    int y, m, d, h, min, s, status, code;
} record;

int get_file_size_in_bytes(FILE *file);
record read_record_from_file(FILE *file, int index);
void write_record_in_file(FILE *file, const record *record_to_write, int index);
void swap_records_in_file(FILE *file, int record_index1, int record_index2);
void print_record(const record *rec);
void remove_end_line(char *str, size_t len);
int safe_scan(int *num);
record get_record(int *code);
int compare(record rec1, record rec2);
int handle_one(FILE *file);
void handle_two(FILE *file);
void handle_three(FILE *file, const record *new);

int main() {
    char *file_name = NULL;
    size_t cap, len = getline(&file_name, &cap, stdin);
    if (file_name != NULL) {
        remove_end_line(file_name, len);
        FILE *file = fopen(file_name, "rb");
        if (file != NULL) {
            fclose(file);
            int par, code = safe_scan(&par);
            if (code == 0) {
                if (par == 0) {
                    file = fopen(file_name, "rb");
                    if (file != NULL) {
                        code = handle_one(file);
                        fclose(file);
                    } else {
                        printf("n/a");
                        code = 0;
                    }
                } else if (par == 1) {
                    file = fopen(file_name, "r+b");
                    if (file != NULL) {
                        handle_two(file);
                        code = handle_one(file);
                        fclose(file);
                    } else {
                        printf("n/a");
                        code = 0;
                    }
                } else if (par == 2) {
                    file = fopen(file_name, "a+b");
                    if (file != NULL) {
                        record new = get_record(&code);
                        if (code != ERROR) {
                            handle_three(file, &new);
                            fclose(file);
                            file = fopen(file_name, "r+b");
                            if (file != NULL) {
                                handle_two(file);
                                handle_one(file);
                                fclose(file);
                            } else {
                                printf("n/a");
                                code = 0;
                            }
                        } else {
                            printf("n/a");
                            code = 0;
                            fclose(file);
                        }
                    } else {
                        printf("n/a");
                        code = 0;
                    }
                } else {
                    printf("n/a");
                    code = 0;
                }
            } else {
                printf("n/a");
                code = 0;
            }

            if (code == ERROR) {
                printf("n/a");
            }
        } else {
            printf("n/a");
        }
        free(file_name);
    } else {
        printf("n/a");
    }

    return 0;
}

void swap_records_in_file(FILE *file, int record_index1, int record_index2) {
    record record1 = read_record_from_file(file, record_index1);
    record record2 = read_record_from_file(file, record_index2);

    write_record_in_file(file, &record1, record_index2);
    write_record_in_file(file, &record2, record_index1);
}

record get_record(int *code) {
    record res;
    char sym = 0;
    int sc = scanf("%d%d%d%d%d%d%d%d%c", &res.y, &res.m, &res.d, &res.h,
                   &res.min, &res.s, &res.status, &res.code, &sym);
    if (!((sc == 8 && sym == 0) || (sc == 9 && sym == '\n')) || res.status > 1 || res.status < 0) {
        *code = ERROR;
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

void write_record_in_file(FILE *file, const record *record_to_write, int index) {
    int offset = index * sizeof(record);
    fseek(file, offset, SEEK_SET);

    fwrite(record_to_write, sizeof(record), 1, file);

    fflush(file);

    rewind(file);
}

void print_record(const record *rec) {
    printf("%d %d %d %d %d %d %d %d", rec->y, rec->m, rec->d,
           rec->h, rec->min, rec->s, rec->status, rec->code);
}

void remove_end_line(char *str, size_t len) {
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int safe_scan(int *num) {
    char sym = 0;
    int res = 0, sc = scanf("%d%c", num, &sym);
    if (!((sc == 1 && sym == 0) || (sc == 2 && sym == '\n'))) {
        res = ERROR;
    }
    return res;
}

int handle_one(FILE *file) {
    int res = ERROR;

    size_t rec_size = get_file_size_in_bytes(file) / sizeof(record);

    for (size_t i = 0; i + 1 < rec_size; ++i) {
        record rec = read_record_from_file(file, i);
        print_record(&rec);
        printf("\n");
        res = 0;
    }

    if (rec_size != 0) {
        record rec = read_record_from_file(file, rec_size - 1);
        print_record(&rec);
        res = 0;
    }

    return res;
}

int compare(record rec1, record rec2) {
    int res = 1;
    if (rec2.y > rec1.y) {
        res = 0;
    } else if (rec2.y == rec1.y) {
        if (rec2.m > rec1.m) {
            res = 0;
        } else if (rec2.m == rec1.m) {
            if (rec2.d > rec1.d) {
                res = 0;
            } else if (rec2.d == rec1.d) {
                if (rec2.h > rec1.h) {
                    res = 0;
                } else if (rec2.h == rec1.h) {
                    if (rec2.min > rec1.min) {
                        res = 0;
                    } else if (rec2.min == rec1.min) {
                        if (rec2.s > rec1.s) {
                            res = 0;
                        }
                    }
                }
            }
        }
    }

    return res;
}

void handle_two(FILE *file) {
    size_t rec_size = get_file_size_in_bytes(file) / sizeof(record);
    for (size_t i = 0; i + 1 < rec_size; ++i) {
        for (size_t j = 0; j + 1 + i < rec_size; ++j) {
            record rec1 = read_record_from_file(file, j + 1), rec2 = read_record_from_file(file, j);
            if (compare(rec1, rec2) == 0) {
                swap_records_in_file(file, j, j + 1);
            }
        }
    }
}

void handle_three(FILE *file, const record *new) {
    size_t rec_size = get_file_size_in_bytes(file) / sizeof(record);
    write_record_in_file(file, new, rec_size);
}
