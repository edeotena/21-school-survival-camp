#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "database.h"

status_event read_record_status_file(FILE *file, int index);
void write_record_status_file(FILE *file, const status_event *record_to_write, int index);
int get_records_count_status_file(FILE *file);
void print_status_record(status_event read);

void select_status(FILE *file, int size) {
    int max = get_records_count_status_file(file);
    if (size > max || size == -1) {
        size = max;
    }

    for (int i = 0; i < size; ++i) {
        status_event read = read_record_status_file(file, i);
        print_status_record(read);
    }
}

void insert_status(FILE *file, const int *values) {
    status_event new;
    new.id = get_records_count_status_file(file);
    new.module = values[0];
    new.status = values[1];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(new.time, sizeof(new.time), "%H:%M:%S", t);
    strftime(new.date, sizeof(new.date), "%d.%m.%Y", t);

    write_record_status_file(file, &new, get_records_count_status_file(file));
}

int get_status_id(int id) {
    int offset = -1;
    FILE *index = fopen("../materials/index_statuses.db", "rb");
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

int *get_modules_statuses(FILE *file, int len) {
    int size = (int)get_records_count_status_file(file);
    int *res = (int *) calloc (len, sizeof(int));
    if (res != NULL) {
        for (int i = 0; i < len; ++i) {
            res[i] = -1;
        }
        for (int i = 0; i < size; ++i) {
                status_event new = read_record_status_file(file, i);
                if (new.module < len && new.status == 1) {
                    res[new.module] = 1;
                } else if (new.module < len) {
                    res[new.module] = -1;
                }
        }
    }
    return res;
}

void update_status(FILE *file, const int *values, int offset, int id) {
    status_event new;
    new.id = id;
    new.module = values[0];
    new.status = values[1];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(new.time, sizeof(new.time), "%H:%M:%S", t);
    strftime(new.date, sizeof(new.date), "%d.%m.%Y", t);

    write_record_status_file(file, &new, offset);
}

void write_record_status_file(FILE *file, const status_event *record_to_write, int index) {
    int offset = index * sizeof(status_event);
    fseek(file, offset, SEEK_SET);

    fwrite(record_to_write, sizeof(status_event), 1, file);
    fflush(file);

    rewind(file);
}

status_event read_record_status_file(FILE *file, int index) {
    int offset = index * sizeof(status_event);
    fseek(file, offset, SEEK_SET);

    status_event record;
    fread(&record, sizeof(status_event), 1, file);

    rewind(file);
    return record;
}

int get_file_size_in_bytes(FILE *file) {
    int size = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    return size;
}

int get_records_count_status_file(FILE *file) {
    return get_file_size_in_bytes(file) / sizeof(status_event);
}

void print_status_record(status_event read) {
    printf("%d %d %d %s %s\n", read.id, read.module, read.status, read.date, read.time);
}

int set_status_index() {
    int res = 1;
    FILE *file = fopen("../materials/master_status_events.db", "rb");
    FILE *index = fopen("../materials/index_statuses.db", "wb");
    if (index != NULL && file != NULL) {
        int size = (int) get_records_count_status_file(file);
        for (int i = 0; i < size; ++i) {
            status_event st = read_record_status_file(file, i);
            indexes new;
            new.id = st.id;
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
