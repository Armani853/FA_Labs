#include "../include/functions.h"

void print_err(StatusCode st) {
    if (st == STATUS_OK) {
        return;
    }

    switch(st) {
        case INVALID_INPUT:
            printf("Неверный ввод\n");
            break;
        case MEMORY_ERROR:
            printf("Ошибка с выделением памяти\n");
            break;
        case OPEN_ERROR:
            printf("Ошибка с открытием файла\n");
            break;
        case ERROR_SYNTAX:
            printf("Неверный символ\n");
            break;
        case DIV_BY_ZERO:
            printf("Деление на ноль\n");
            break;
        case UNINIT_VAR:
            printf("Неинициализированная переменная\n");
            break;
        default:
            printf("Неизвестная ошибка\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Должно быть 3 аргумента\n");
        return 1;
    }
    const char* input_filename = argv[1];
    const char* log_filename = argv[2];

    FILE* input_file = NULL;
    Interpreter_state state = {0};
    StatusCode init_st = STATUS_OK;
    StatusCode exec_st = STATUS_OK;

    init_st = init_inter(&state, log_filename);
    if (init_st != STATUS_OK) {
        print_err(init_st);
        return 1;
    }
    input_file = fopen(input_filename, "r");
    if (!input_file) {
        print_err(OPEN_ERROR);
        if (state.log_file) {
            fclose(state.log_file);
            state.log_file = NULL;
        }
        return 1;
    }
    char line[MAX_LINE_LENGTH];
    printf("Основной цикл обработки\n");
    printf("Лог пишется в %s\n", log_filename);
    while (fgets(line, sizeof(line), input_file) != NULL) {
        if (strlen(line) <= 1) {
            continue;
        }
        exec_st = execute_line(&state, line);
        if (exec_st != STATUS_OK) {
            print_err(exec_st);
            break;
        }
    }
    if (input_file) {
        fclose(input_file);
        if (state.log_file) {
            fclose(state.log_file);
            state.log_file = NULL;
        }
    }
    printf("Интерпретатор завершил работу!\n");
    if (exec_st == STATUS_OK) {
        return 0;
    } else {
        return 1;
    }

}