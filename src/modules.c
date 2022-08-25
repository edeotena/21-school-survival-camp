#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "database.h"

module read_record_module_file(FILE *file, int index);
void write_record_module_file(FILE *file, const module *record_to_write, int index);
int get_records_count_module_file(FILE *file);
void print_module_record(module read);

void select_active_module(FILE *file, int size) {
    int max = get_records_count_module_file(file);
    if (size > max || size == -1) {
        size = max;
    }

    for (int i = 0; i < size; ++i) {
        module read = read_record_module_file(file, i);
        if (read.status != DELETED) {
            print_module_record(read);
        } else if (size < max) {
            ++size;
        }
    }
}

void select_module(FILE *file, const int *modules) {
    int max = get_records_count_module_file(file);

    for (int i = 0; i < max; ++i) {
        if (modules[i] == 1) {
            module read = read_record_module_file(file, i);
            print_module_record(read);
        }
    }
}

void insert_module(FILE *file, const int *values, char name[30]) {
    size_t size = strlen(name);
    if (size < 23) {
        name[size] = ' ';
        name[size + 1] = 'm';
        name[size + 2] = 'o';
        name[size + 3] = 'd';
        name[size + 4] = 'u';
        name[size + 5] = 'l';
        name[size + 6] = 'e';
        name[size + 7] = '\0';
    }
    module mod;
    strcpy(mod.name, name);
    mod.cell = values[1];
    mod.id = get_records_count_module_file(file);
    mod.level = values[0];
    mod.status = 0;
    write_record_module_file(file, &mod, get_records_count_module_file(file));
}

int get_module_id(int id) {
    int offset = -1;
    FILE *index = fopen("../materials/index_modules.db", "rb");
    if (index != NULL) {
        int size = get_file_size_in_bytes(index) / sizeof(indexes);
        int l = 0, r = size;
        while (l <= r && offset == -1) {
            indexes new = read_record_index_file(index, l + (r - l) / 2);
            if (new.id > id) {
                r = r - (r - l) / 2 - 1;
            } else if (new.id < id) {
                l = l + (r - l) / 2 + 1;
            } else {
                offset = new.offset;
            }
        }
        fclose(index);
    }
    return offset;
}

void update_module(FILE *file, const int *values, char name[30], int offset, int id) {
    module mod = read_record_module_file(file, offset);
    if (name[0] != ' ' && strlen(name) < 23) {
        size_t size = strlen(name);
        name[size] = ' ';
        name[size + 1] = 'm';
        name[size + 2] = 'o';
        name[size + 3] = 'd';
        name[size + 4] = 'u';
        name[size + 5] = 'l';
        name[size + 6] = 'e';
        name[size + 7] = '\0';
        strcpy(mod.name, name);
    }
    mod.cell = values[1];
    mod.level = values[0];
    mod.id = id;
    write_record_module_file(file, &mod, offset);
}

void delete_module(FILE *file, int offset) {
    module mod = read_record_module_file(file, offset);
    mod.status = DELETED;
    write_record_module_file(file, &mod, offset);
}

void write_record_module_file(FILE *file, const module *record_to_write, int index) {
    int offset = index * sizeof(module);
    fseek(file, offset, SEEK_SET);

    fwrite(record_to_write, sizeof(module), 1, file);
    fflush(file);

    rewind(file);
}

void write_record_index_file(FILE *file, const indexes *record_to_write, int index) {
    int offset = index * sizeof(indexes);
    fseek(file, offset, SEEK_SET);

    fwrite(record_to_write, sizeof(indexes), 1, file);
    fflush(file);

    rewind(file);
}

indexes read_record_index_file(FILE *file, int index) {
    int offset = index * sizeof(indexes);
    fseek(file, offset, SEEK_SET);

    indexes record;
    fread(&record, sizeof(indexes), 1, file);

    rewind(file);
    return record;
}

module read_record_module_file(FILE *file, int index) {
    int offset = index * sizeof(module);
    fseek(file, offset, SEEK_SET);

    module record;
    fread(&record, sizeof(module), 1, file);

    rewind(file);
    return record;
}

int get_records_count_module_file(FILE *file) {
    return get_file_size_in_bytes(file) / sizeof(module);
}

void print_module_record(module read) {
    printf("%d %s %d %d %d\n", read.id, read.name, read.level, read.cell, read.status);
}

int *get_modules_zero_cell(FILE *file) {
    int size = (int)get_records_count_module_file(file);
    int *res = (int *) calloc (size, sizeof(int));
    if (res != NULL) {
        for (int i = 0; i < size; ++i) {
            module new = read_record_module_file(file, i);
            if (new.level == 0 || new.cell == 0) {
                res[i] = 1;
            } else {
                res[i] = -1;
            }
        }
    }
    return res;
}

int *get_modules_deleted(FILE *file) {
    int size = (int)get_records_count_module_file(file);
    int *res = (int *) calloc (size, sizeof(int));
    if (res != NULL) {
        for (int i = 0; i < size; ++i) {
            module new = read_record_module_file(file, i);
            if (new.status == DELETED) {
                res[i] = 1;
            } else {
                res[i] = -1;
            }
        }
    }
    return res;
}

int set_module_index() {
    int res = 1;
    FILE *file = fopen("../materials/master_modules.db", "rb");
    FILE *index = fopen("../materials/index_modules.db", "wb");
    if (index != NULL && file != NULL) {
        int size = (int) get_records_count_module_file(file);
        for (int i = 0; i < size; ++i) {
            module mod = read_record_module_file(file, i);
            indexes new;
            new.id = mod.id;
            new.offset = i;
            write_record_index_file(index, &new, i);
        }
        fclose(file);
        fclose(index);
    } else {
        res = 0;
        printf("File error!\n");
    }
    return res;
}

void swap_indexes_in_file(FILE *file, int record_index1, int record_index2) {
    indexes idx1 = read_record_index_file(file, record_index1);
    indexes idx2 = read_record_index_file(file, record_index2);

    write_record_index_file(file, &idx1, record_index2);
    write_record_index_file(file, &idx2, record_index1);
}


void sort_indexes(FILE *file) {
    size_t rec_size = get_file_size_in_bytes(file) / sizeof(indexes);
    for (size_t i = 0; i + 1 < rec_size; ++i) {
        for (size_t j = 0; j + 1 + i < rec_size; ++j) {
            indexes idx1 = read_record_index_file(file, j + 1), idx2 = read_record_index_file(file, j);
            if (idx1.id < idx2.id) {
                swap_indexes_in_file(file, j, j + 1);
            }
        }
    }
}
