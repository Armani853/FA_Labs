#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"

#define MAX_LINE_LENGTH 1024

StatusCode process_file(const char* input, const char* output, char operation_code) {
    FILE* in_file = NULL;
    FILE* out_file = NULL;
    StatusCode status = STATUS_OK;
    char buffer[MAX_LINE_LENGTH];

    in_file = fopen(input, "r");
    if (in_file == NULL) {
        return FILE_OPEN_ERROR;
    }

    out_file = fopen(output, "w");
    if (out_file == NULL) {
        fclose(in_file);
        return FILE_OPEN_ERROR;
    }

    while (fgets(buffer, sizeof(buffer), in_file) != NULL) {
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        int i;
        int count_lat = 0;
        int count_ex = 0;
        switch (operation_code) {
            case 'd':
                for (i = 0; buffer[i] != '\0'; i++) {
                    if (!isdigit(buffer[i])) {
                        fputc(buffer[i], out_file);
                    }
                }
                fputc('\n', out_file);
                break;
            case 'i':
                for (i = 0; buffer[i] != '\0'; i++) {
                    if (isalpha(buffer[i])) {
                        count_lat++;
                    }
                }
                fprintf(out_file, "%d\n", count_lat);
                break;
            case 's':
                for (i = 0; buffer[i] != '\0'; i++) {
                    if (!isalpha(buffer[i]) && !isdigit(buffer[i]) && buffer[i] != ' ') {
                        count_ex++;
                    }
                }
                fprintf(out_file, "%d\n", count_ex);
                break;
            case 'a':
                for (i = 0; buffer[i] != '\0'; i++) {
                    if (isdigit(buffer[i])) {
                        fputc(buffer[i], out_file);
                    } else {
                        fprintf(out_file, "[%02X]", (unsigned char)buffer[i]);
                    }
                }
                fputc('\n', out_file);
                break;
            default:
                status = UKNOWN_FLAG;
                break;
        }
        if (status != STATUS_OK) {
            break;
        }
    }
    fclose(in_file);
    fclose(out_file);
    return status;    
}