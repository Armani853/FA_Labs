#include "../include/functions.h"
#include <stdio.h>
void print_status(StatusCode s) {
    switch(s) {
        case STATUS_OK:
            printf("Успешно\n");
            break;
        case INVALID_INPUT:
            printf("Неверный ввод\n");
            break;
        case MAX_ITER_ERROR:
            printf("Максимальное количество выполнений превышено\n");
            break;
        default:
            printf("Неизвестная ошибка\n");
            break;
    }
}

void print_res(const int base, const double epsilon, const int num_fractions, const double fractions[], const bool results[]) {
    printf("Результаты проверки при основании %d и эпсилоне %.1e\n", base, epsilon);
    for (int i = 0; i < num_fractions; i++) {
        if (results[i]) {
            printf("Дробь %lf Представление в %d: %s\n", fractions[i], base, "Конечное");
        } else {
            printf("Дробь %lf Представление в %d: %s\n", fractions[i], base, "Бесконечное");
        }
    }
}


StatusCode validate_base(const int base) {
    if (base < 2) {
        return INVALID_INPUT;
    }
    return STATUS_OK;
}

StatusCode validate_fraction(const double fraction, const double epsilon) {
    if (IS_LESS_OR_EQUAL(fraction, 0.0, epsilon) || IS_MORE_OR_EQUAL(fraction, 1.0, epsilon)) {
        return INVALID_INPUT;
    }
    return STATUS_OK;
}

StatusCode check_finite(const int base, const double epsilon, const int max_iter, bool* result_buffer, const int num_fractions, ...) {
    if (result_buffer == NULL) {
        return INVALID_INPUT;
    }
    StatusCode base_status = validate_base(base);
    if (base_status != STATUS_OK) {
        return base_status;
    } 

    if (num_fractions <= 0 || max_iter <= 0 || epsilon <= 0) {
        return INVALID_INPUT;
    }

    va_list args;
    va_start(args, num_fractions);
    for (int i = 0; i < num_fractions; i++) {
        double curr = va_arg(args, double);
        StatusCode frac_status = validate_fraction(curr, epsilon);
        if (frac_status != STATUS_OK) {
            va_end(args);
            return INVALID_INPUT;
        }
        double rem = curr;
        bool is_fin = false;
        for (int iter = 0; iter < max_iter; iter++) {
            rem *= base;
            double int_p;
            double frac_p = modf(rem, &int_p);
            rem = frac_p;
            if (IS_EQUAL(rem, 0.0, epsilon)) {
                is_fin = true;
                break;
            }
        }
        result_buffer[i] = is_fin;
    }
    va_end(args);
    return STATUS_OK;
}