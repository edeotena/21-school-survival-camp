#include "logger.h"
#include "time.h"

FILE* log_init(char *filename) {
    FILE *res = fopen(filename, "a");
    return res;
}

int logcat(FILE* log_file, char *message, log_level level) {
    time_t current_time;
    struct tm *time_info;
    char timeString[9];

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);

    fprintf(log_file, "[");


    if (level == debug) {
        fprintf(log_file, "DEBUG");
    } else if (level == trace) {
        fprintf(log_file, "TRACE");
    } else if (level == info) {
        fprintf(log_file, "INFO");
    } else if (level == warning) {
        fprintf(log_file, "WARNING");
    } else if (level == error) {
        fprintf(log_file, "ERROR");
    }

    fprintf(log_file, "] ");

    fprintf(log_file, timeString);
    fprintf(log_file, " ");
    fprintf(log_file, message);
    fprintf(log_file, "\n");

    return 0;
}

int log_close(FILE* log_file) {
    fclose(log_file);
    return 0;
}
