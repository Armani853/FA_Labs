#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

#define MIN_ARGS 3
#define MAX_ARGS 4
#define OUT_PREFIX "out_"

int main(int argc, char* argv[]) {
    char* flag;
    char* input;
    char* output;
    char generated_buffer[256];
    if (argc > MAX_ARGS || argc < MIN_ARGS) {
        return INVALID_INPUT;
    }
    flag = argv[1];
    input = argv[2];

    if (strlen(flag) < 2 || (flag[0] != '-' && flag[0] != '/')) {
        return INVALID_INPUT;
    }
    
    if (flag[1] == 'n') {
        if (argc != MAX_ARGS) {
            return INVALID_INPUT;
        }
        output = argv[3];
        if (strlen(flag) != 3) {
            return INVALID_INPUT;
        }
    } else {
        if (argc != MIN_ARGS) {
            return INVALID_INPUT;
        }
        snprintf(generated_buffer, sizeof(generated_buffer), "%s%s", OUT_PREFIX, input);
        output = generated_buffer;

        if (strlen(flag) != 2) {
            return INVALID_INPUT;
        }
    }

    printf("Входной файл: %s, Выходной файл: %s, Флаг: %s\n", input, output, flag);
    char operation_code = (flag[1] == 'n') ? flag[2] : flag[1];
    StatusCode status = process_file(input, output, operation_code);

    switch (status) {
        case STATUS_OK:
            printf("Обработка завершена успешно\n");
            break;
        case INVALID_INPUT:
            printf("Ошибка с вводом");
            break;
        case FILE_OPEN_ERROR:
            printf("Ошибка с открытием файла");
            break;
        case UKNOWN_FLAG:
            printf("Неизвестный флаг");
            break;
        default:
            printf("Неизвестная ошибка");
            break;
    }

    return 0;
}