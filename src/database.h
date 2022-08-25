#ifndef SRC_DATABASE_H_
#define SRC_DATABASE_H_

#define DELETED 1

typedef struct {
    int id;
    char name[30];
    int level;
    int cell;
    int status;
} module;

typedef struct {
    int level;
    int cell;
    int security;
} level;

typedef struct {
    int id;
    int module;
    int status;
    char date[11];
    char time[9];
} status_event;

typedef struct {
    int id;
    int offset;
} indexes;

void select_active_module(FILE *file, int size);
void select_module(FILE *file, const int *modules);
void insert_module(FILE *file, const int *values, char name[30]);
int get_module_id(int id);
int *get_modules_zero_cell(FILE *file);
int *get_modules_deleted(FILE *file);
void update_module(FILE *file, const int *values, char name[30], int offset, int id);
void delete_module(FILE *file, int offset);
int set_module_index();

void select_level(FILE *file, int size);
void insert_level(FILE *file, const int *values);
int get_level(int id);
void update_level(FILE *file, const int *values, int offset, int type);
int set_level_index();

void select_status(FILE *file, int size);
void insert_status(FILE *file, const int *values);
int get_status_id(int id);
int *get_modules_statuses(FILE *file, int len);
void update_status(FILE *file, const int *values, int offset, int id);
int set_status_index();

int get_file_size_in_bytes(FILE *file);
void write_record_index_file(FILE *file, const indexes *record_to_write, int index);
void sort_indexes(FILE *file);
indexes read_record_index_file(FILE *file, int index);

#endif  // SRC_DATABASE_H_
