#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "converter.h"

#define MAX_INPUTS 100
#define MAX_STR 64

int main() {
    int base;
    printf("Введите основание системы счисления от 2 до 36: ");
    if (scanf("%d", &base) != 1) {
        return INVALID_INPUT;
    }
    if (base < 2 || base > 36) {
        return INVALID_INPUT;
    }
    while (getchar() != '\n');
    const char* inputs[MAX_INPUTS];
    char storage[MAX_INPUTS][MAX_STR];
    int count = 0;
    printf("Введите числа в системе счисления с основанием %d (Введите Stop для завершения ввода)", base);
    while (count < MAX_INPUTS) {
        printf("> ");
        if (!fgets(storage[count], MAX_STR, stdin)) {
            break;
        }
        int len = strlen(storage[count]);
        if (len > 0 && storage[count][len - 1] == '\n') {
            storage[count][len - 1] = '\0';
        }
        if (strcmp(storage[count], "Stop") == 0) {
            break;
        }
        if (!is_valid_number(storage[count], base)) {
            printf("Некорректное число для основания %d\n", base);
            continue;
        }
        inputs[count] = storage[count];
        count++;
    }
    if (count == 0) {
        return INVALID_INPUT;
    }
    long long max_abs_value;
    StatusCode status = find_max_abs(inputs, count, base, &max_abs_value);
    if (status != STATUS_OK) {
        return status;
    }

    char original_str[MAX_STR];
    int_to_str(max_abs_value, base, original_str, MAX_STR);

    char cleaned_str[MAX_STR];
    strcpy(cleaned_str, original_str);
    if (cleaned_str[0] == '-' || cleaned_str[0] == '+') {
        char* start = cleaned_str + 1;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }
        memmove(cleaned_str + 1, start, strlen(start) + 1);
    } else {
        char* start = cleaned_str;
        while (*start == '0' && *(start + 1) != '\0') {
            start++;
        }
        strcpy(cleaned_str, start);
    }

    printf("Максимальное по модулю число: %s\n", cleaned_str);

    int bases[] = {9, 18, 27, 36};
    for (int i = 0; i < 4; i++) {
        char buff[MAX_STR];
        int_to_str(max_abs_value, bases[i], buff, MAX_STR);
        printf("Основание %d: %s\n", bases[i], buff);
    }

    return STATUS_OK;
}