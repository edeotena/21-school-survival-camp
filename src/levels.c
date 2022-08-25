#include <stdio.h>

#include "database.h"

level read_record_level_file(FILE *file, int index);
void write_record_level_file(FILE *file, const level *record_to_write, int index);
int get_records_count_level_file(FILE *file);
void print_level_record(level read);

void select_level(FILE *file, int size) {
    int max = get_records_count_level_file(file);
    if (size > max || size == -1) {
        size = max;
    }

    for (int i = 0; i < size; ++i) {
        level read = read_record_level_file(file, i);
        print_level_record(read);
    }
}

void insert_level(FILE *file, const int *values) {
    level new;
    new.level = get_records_count_level_file(file) + 1;
    new.cell = values[0];
    new.security = values[1];
    write_record_level_file(file, &new, get_records_count_level_file(file));
}

int get_level(int id) {
    int offset = -1;
    FILE *index = fopen("../materials/index_levels.db", "rb");
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

void update_level(FILE *file, const int *values, int offset, int type) {
    level new = read_record_level_file(file, offset);
    if (type == -1) {
        new.security = values[0];
    } else {
        new.level = type;
        new.cell = values[0];
        new.security = values[1];
    }
    write_record_level_file(file, &new, offset);
}

void write_record_level_file(FILE *file, const level *record_to_write, int index) {
    int offset = index * sizeof(level);
    fseek(file, offset, SEEK_SET);

    fwrite(record_to_write, sizeof(level), 1, file);
    fflush(file);

    rewind(file);
}

level read_record_level_file(FILE *file, int index) {
    int offset = index * sizeof(level);
    fseek(file, offset, SEEK_SET);

    level record;
    fread(&record, sizeof(level), 1, file);

    rewind(file);
    return record;
}

int get_records_count_level_file(FILE *file) {
    return get_file_size_in_bytes(file) / sizeof(level);
}

void print_level_record(level read) {
    printf("%d %d %d \n", read.level, read.cell, read.security);
}

int set_level_index() {
    int res = 1;
    FILE *file = fopen("../materials/master_levels.db", "rb");
    FILE *index = fopen("../materials/index_levels.db", "wb");
    if (index != NULL && file != NULL) {
        int size = (int) get_records_count_level_file(file);
        for (int i = 0; i < size; ++i) {
            level lvl = read_record_level_file(file, i);
            indexes new;
            new.id = lvl.level;
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
