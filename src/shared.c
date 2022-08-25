#include <stdio.h>

#include "shared.h"
#include "database.h"
#include "input_utils.h"
#include "array_utils.h"

void select(int db) {
    if (db == 1) {
        FILE *file = fopen("../materials/master_modules.db", "rb");
        if (file != NULL) {
            printf("Insert the number of records or leave empty to output all of them:\n");
            int code = 0, len = 0, *input = safe_scan(&len, &code);
            if (code == 0 && len == 1 && input[0] >= 0) {
                select_active_module(file, input[0]);
            } else if (code == 0 && len == 0) {
                select_active_module(file, -1);
            } else {
                printf("Wrong input\n");
            }
            safe_free_arr(&input);
            fclose(file);
        } else {
            printf("Not found ../materials/master_modules.db\n");
        }
    } else if (db == 2) {
        FILE *file = fopen("../materials/master_levels.db", "rb");
        if (file != NULL) {
            printf("Insert the number of records or leave empty to output all of them:\n");
            int code = 0, len = 0, *input = safe_scan(&len, &code);
            if (code == 0 && len == 1 && input[0] >= 0) {
                select_level(file, input[0]);
            } else if (code == 0 && len == 0) {
                select_level(file, -1);
            } else {
                printf("Wrong input\n");
            }
            safe_free_arr(&input);
            fclose(file);
        } else {
            printf("Not found ../materials/master_levels.db\n");
        }
    } else if (db == 3) {
        FILE *file = fopen("../materials/master_status_events.db", "rb");
        if (file != NULL) {
            printf("Insert the number of records or leave empty to output all of them:\n");
            int code = 0, len = 0, *input = safe_scan(&len, &code);
            if (code == 0 && len == 1 && input[0] >= 0) {
                select_status(file, input[0]);
            } else if (code == 0 && len == 0) {
                select_status(file, -1);
            } else {
                printf("Wrong input\n");
            }
            safe_free_arr(&input);
            fclose(file);
        } else {
            printf("Not found ../materials/master_status_events.db\n");
        }
    } else {
        printf("Wrong input\n");
    }
}

void insert(int db) {
    if (db == 1) {
        FILE *file = fopen("../materials/master_modules.db", "ab");
        if (file != NULL) {
            printf("Input module record (name level cell):\n");
            char name[30];
            scanf("%29s", name);
            int code = 0, len = 0, *input = safe_scan(&len, &code);
            if (code == 0 && len == 2 && input[0] >= 0) {
                insert_module(file, input, name);
                set_sort_indexes();
            } else {
                printf("Wrong input\n");
            }
            safe_free_arr(&input);
            fclose(file);
        } else {
            printf("Not found ../materials/master_modules.db\n");
        }
    } else if (db == 2) {
        FILE *file = fopen("../materials/master_levels.db", "ab");
        if (file != NULL) {
            printf("Input level record (cells protect_flag):\n");
            int code = 0, len = 0, *input = safe_scan(&len, &code);
            if (code == 0 && len == 2) {
                insert_level(file, input);
                set_sort_indexes();
            } else {
                printf("Wrong input\n");
            }
            safe_free_arr(&input);
            fclose(file);
        } else {
            printf("Not found ../materials/master_levels.db\n");
        }
    } else if (db == 3) {
        FILE *file = fopen("../materials/master_status_events.db", "ab");
        if (file != NULL) {
            printf("Input status event record (module_id status):\n");
            int code = 0, len = 0, *input = safe_scan(&len, &code);
            if (code == 0 && len == 2 && input[0] >= 0) {
                insert_status(file, input);
                set_sort_indexes();
            } else {
                printf("Wrong input\n");
            }
            safe_free_arr(&input);
            fclose(file);
        } else {
            printf("Not found ../materials/master_status_events.db\n");
        }
    } else {
        printf("Wrong input\n");
    }
}

void update(int db) {
    if (db == 1) {
        FILE *file = fopen("../materials/master_modules.db", "rb+");
        if (file != NULL) {
            printf("Input ID:\n");
            int len_id = 0, code_id = 0, *id = safe_scan(&len_id, &code_id);
            if (len_id == 1 && code_id == 0) {
                int offset = get_module_id(id[0]);
                if (offset != -1) {
                    printf("Input new module record (name level cell):\n");
                    char name[30];
                    scanf("%29s", name);
                    int code = 0, len = 0, *input = safe_scan(&len, &code);
                    if (code == 0 && len == 2) {
                        update_module(file, input, name, offset, *id);
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
    } else if (db == 2) {
        FILE *file = fopen("../materials/master_levels.db", "rb+");
        if (file != NULL) {
            printf("Input level:\n");
            int len_id = 0, code_id = 0, *id = safe_scan(&len_id, &code_id);
            if (len_id == 1 && code_id == 0) {
                int offset = get_level(id[0]);
                if (offset != -1) {
                    printf("Input level record (cells protect_flag):\n");
                    int code = 0, len = 0, *input = safe_scan(&len, &code);
                    if (code == 0 && len == 2) {
                        update_level(file, input, offset, *id);
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
    } else if (db == 3) {
        FILE *file = fopen("../materials/master_status_events.db", "rb+");
        if (file != NULL) {
            printf("Input ID:\n");
            int len_id = 0, code_id = 0, *id = safe_scan(&len_id, &code_id);
            if (len_id == 1 && code_id == 0) {
                int offset = get_status_id(id[0]);
                if (offset != -1) {
                    printf("Input status event record (module_id status):\n");
                    int code = 0, len = 0, *input = safe_scan(&len, &code);
                    if (code == 0 && len == 2 && input[0] >= 0) {
                        update_status(file, input, offset, *id);
                    } else {
                        printf("Wrong input\n");
                    }
                    safe_free_arr(&input);
                } else {
                        printf("No such id status\n");
                    }
                } else {
                    printf("Wrong input\n");
                }
            fclose(file);
            safe_free_arr(&id);
        } else {
            printf("Not found ../materials/master_status_events.db\n");
        }
    } else {
        printf("Wrong input\n");
    }
}

void delete(const char *str) {
    FILE *file = fopen("../materials/master_modules.db", "rb+");
    if (file != NULL) {
        printf("%s", str);
        int len_id = 0, code_id = 0, *id = safe_scan(&len_id, &code_id);
        if (code_id == 0) {
            for (int i = 0; i < len_id; ++i) {
                int offset = get_module_id(id[i]);
                if (offset != -1) {
                    delete_module(file, offset);
                    printf("Module %d marked as deleted\n", id[i]);
                } else {
                    printf("No %d id module\n", id[i]);
                }
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
