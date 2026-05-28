#include <stdio.h>
#include <time.h>

#include "request.h"

#define MAX_ARG_COUNT 2
#define MIN_ARG_COUNT 2

int main(int argc, char *argv[]) {
    if (argc > MAX_ARG_COUNT) {
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }
    if (argc < MIN_ARG_COUNT) {
        return 1;
    }

    response_data rd = ping(argv[1]);

    printf("\n\nServer responded with status code %ld\n\n", rd.response_code);

    FILE *file = NULL;

    file = fopen("log.txt", "a");

    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    time_t now = (unsigned)time(NULL);
    char formatted_iso_time[20];

    time(&now);
    struct tm *tm_info = gmtime(&now);

    strftime(formatted_iso_time, sizeof(formatted_iso_time), "%Y-%m-%dT%H:%M:%S", tm_info);

    fprintf(file, "[LOG] %s Server responded with status code %ld\n", formatted_iso_time, rd.response_code);
    fclose(file);

    return 0;
}
