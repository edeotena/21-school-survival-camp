#include <stdio.h>

#include "input_utils.h"
#include "array_utils.h"
#include "shared.h"
#include "database.h"

void print_main();
void handle_select();
void handle_insert();
void handle_update();
void handle_delete();
void handle_active_modules();
void handle_delete_modules();
void handle_protected();
void handle_move_module();
void handle_set_level_protect();
int test_end();
int set_sort_indexes();

int main() {
    if (set_sort_indexes()) {
        int code = 0, menu_len = 0, *input = NULL;
        do {
            code = 0;
            print_main();
            safe_free_arr(&input);
            input = safe_scan(&menu_len, &code);
            if (code != ERROR) {
                if (menu_len == 1) {
                    if (input[0] == 1) {
                        handle_select();
                    } else if (input[0] == 2) {
                        handle_insert();
                    } else if (input[0] == 3) {
                        handle_update();
                    } else if (input[0] == 4) {
                        handle_delete();
                    } else if (input[0] == 5) {
                        handle_active_modules();
                    } else if (input[0] == 6) {
                        handle_delete_modules();
                    } else if (input[0] == 7) {
                        handle_protected();
                    } else if (input[0] == 8) {
                        handle_move_module();
                    } else if (input[0] == 9) {
                        handle_set_level_protect();
                    } else if (input[0] == 10) {
                        printf("Stop executing...\n");
                    }
                } else {
                    printf("Input one elem\n");
                }
            } else {
                printf("Wrong input\n");
            }
        } while (!(menu_len == 1 && input[0] == 10 && code == 0));
        safe_free_arr(&input);
        if (test_end() == 1) {
            printf("Main module is dead!\n");
        } else {
            printf("Main module is alive!\n");
        }
    } else {
        printf("File error while creating indexes\n");
    }
    return 0;
}

void print_main() {
    printf("Please choose one operation:\n"
           "1. SELECT\n"
           "2. INSERT\n"
           "3. UPDATE\n"
           "4. DELETE\n"
           "5. Get all active additional modules (last module status is 1)\n"
           "6. Delete modules by ids\n"
           "7. Set protected mode for module by id\n"
           "8. Move module by id to specified memory level and cell\n"
           "9. Set protection flag of the specified memory level\n"
           "10. Exit\n");
}

void handle_select() {
    printf("Please choose a table:\n"
           "1. Modules\n"
           "2. Levels\n"
           "3. Status events\n");
    int len = 0, code = 0, *input = safe_scan(&len, &code);
    if (code != ERROR && len == 1) {
        select(input[0]);
    } else {
        printf("Wrong input\n");
    }
    safe_free_arr(&input);
}

void handle_insert() {
    printf("Please choose a table:\n"
           "1. Modules\n"
           "2. Levels\n"
           "3. Status events\n");
    int len = 0, code = 0, *input = safe_scan(&len, &code);
    if (code != ERROR && len == 1) {
        insert(input[0]);
    } else {
        printf("Wrong input\n");
    }
    safe_free_arr(&input);
}

void handle_update() {
    printf("Please choose a table:\n"
           "1. Modules\n"
           "2. Levels\n"
           "3. Status events\n");
    int len = 0, code = 0, *input = safe_scan(&len, &code);
    if (code != ERROR && len == 1) {
        update(input[0]);
    } else {
        printf("Wrong input\n");
    }
    safe_free_arr(&input);
}

void handle_delete() {
    printf("Delete module by mark\n");
    delete("Input module id:\n");
}
void handle_active_modules() {
    FILE *file = fopen("../materials/master_modules.db", "rb");
    if (file != NULL) {
        int size = get_file_size_in_bytes(file) / sizeof(module);
        fclose(file);
        file = fopen("../materials/master_status_events.db", "rb");
        if (file != NULL) {
            int *modules = get_modules_statuses(file, size);
            if (modules != NULL) {
                fclose(file);
                file = fopen("../materials/master_modules.db", "rb");
                if (file != NULL) {
                    select_module(file, modules);
                    safe_free_arr(&modules);
                    fclose(file);
                } else {
                    printf("Not found ../materials/master_modules.db\n");
                }
            } else {
                printf("File && alloc error\n");
            }
        } else {
            printf("Not found ../materials/master_status_events.db\n");
        }
    } else {
        printf("Not found ../materials/master_modules.db\n");
    }
}
void handle_delete_modules() {
    printf("Delete module's by mark\n");
    delete("Input module's id:\n");
}
void handle_protected() {
    FILE *file = fopen("../materials/master_status_events.db", "ab");
    if (file != NULL) {
        printf("Input module id:\n");
        int code = 0, len = 0, *input = safe_scan(&len, &code);
        if (code == 0 && len == 1 && input[0] >= 0) {
            int temp[2] = {input[0], 0};
            insert_status(file, temp);
            temp[1] = 1;
            insert_status(file, temp);
            temp[1] = 20;
            insert_status(file, temp);
            set_sort_indexes();
        } else {
            printf("Wrong input\n");
        }
        safe_free_arr(&input);
        fclose(file);
    } else {
        printf("Not found ../materials/master_status_events.db\n");
    }
}

void handle_move_module() {
    FILE *file = fopen("../materials/master_modules.db", "rb+");
    if (file != NULL) {
        printf("Input ID:\n");
        int len_id = 0, code_id = 0, *id = safe_scan(&len_id, &code_id);
        if (len_id == 1 && code_id == 0) {
            int offset = get_module_id(id[0]);
            if (offset != -1) {
                printf("Input new module record (level cell):\n");
                int code = 0, len = 0, *input = safe_scan(&len, &code);
                if (code == 0 && len == 2) {
                    update_module(file, input, " ", offset, *id);
                } else {
                    printf("Wrong input\n");
                }
                safe_free_arr(&input);
            } else {
                printf("No such id module\n");
            }
        } else {
            printf("Wrong input\n");
        }
        safe_free_arr(&id);
        fclose(file);
    } else {
        printf("Not found ../materials/master_modules.db\n");
    }
}

void handle_set_level_protect() {
    FILE *file = fopen("../materials/master_levels.db", "rb+");
    if (file != NULL) {
        printf("Input level:\n");
        int len_id = 0, code_id = 0, *id = safe_scan(&len_id, &code_id);
        if (len_id == 1 && code_id == 0) {
            int offset = get_level(id[0]);
            if (offset != -1) {
                printf("Input protect_flag:\n");
                int code = 0, len = 0, *input = safe_scan(&len, &code);
                if (code == 0 && len == 1) {
                    update_level(file, input, offset, -1);
                } else {
                    printf("Wrong input\n");
                }
                safe_free_arr(&input);
            } else {
                printf("No such level\n");
            }
        } else {
            printf("Wrong input\n");
        }
        safe_free_arr(&id);
        fclose(file);
    } else {
        printf("Not found ../materials/master_levels.db\n");
    }
}

int test_end() {
    int res = 0;
    FILE *file = fopen("../materials/master_modules.db", "rb");
    if (file != NULL) {
        int size = (int)get_file_size_in_bytes(file) / sizeof(module);
        int *modules_position = get_modules_zero_cell(file);
        if (modules_position != NULL) {
            int found = 0;
            for (int i = 0; i < size; ++i) {
                if (modules_position[i] == 1) {
                    ++found;
                }
            }
            if (found == 1 && modules_position[0] == 1) {
                int *modules_status = get_modules_deleted(file);
                if (modules_status != NULL) {
                    found = 0;
                    for (int i = 0; i < size; ++i) {
                        if (modules_status[i] == 1) {
                            ++found;
                        }
                    }
                    if (found == size - 1 && modules_status[0] == -1) {
                        res = 1;
                    } else {
                        printf("Additional modules not deleted\n");
                    }
                    safe_free_arr(&modules_status);
                } else {
                    printf("Alloc error\n");
                }
            } else if (found != 0) {
                printf("More then 1 module in 0 level 0 cell\n");
            } else {
                printf("Main is not in 0 level 0 cell\n");
            }
            safe_free_arr(&modules_position);
        } else {
            printf("Alloc error\n");
        }
    } else {
        printf("Not found ../materials/master_modules.db\n");
    }
    return res;
}

int set_sort_indexes() {
    int res = 1;
    if (set_status_index() && set_level_index() && set_module_index()) {
        FILE *file_mod = fopen("../materials/index_modules.db", "rb");
        FILE *file_lvl = fopen("../materials/index_levels.db", "rb");
        FILE *file_status = fopen("../materials/index_statuses.db", "rb");
        sort_indexes(file_mod);
        sort_indexes(file_lvl);
        sort_indexes(file_status);
        fclose(file_mod);
        fclose(file_lvl);
        fclose(file_status);
    } else {
        res = 0;
    }
    return res;
}
