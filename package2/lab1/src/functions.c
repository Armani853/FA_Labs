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

int gcd(long long num, long long denom) {
    while (denom) {
        long long temp = num % denom;
        num = denom;
        denom = temp;
    }
    return num;
}

StatusCode is_finite(const int base, long long num, long long denom, bool* res) {
    if (base < 2 || num <= 0 || denom <= 0 || num >= denom || res == NULL) {
        return INVALID_INPUT;
    }
    int temp_base = base;
    long long com = gcd(num, denom);
    denom /= com;
    for (int i = 2; i * i <= temp_base; i++) {
        if (temp_base % i == 0) {
            while (denom % i == 0) {
                denom /= i;
            }
            while (temp_base % i == 0) {
                temp_base /= i;
            }
        }
    }
    if (temp_base > 1) {
            while (denom % temp_base == 0) {
                denom /= temp_base;
            }
        }
    *res = (denom == 1);
    return STATUS_OK;
}

StatusCode check_finite(const int base, const double epsilon, bool* result_buffer, const int num_fractions, ...) {
    if (result_buffer == NULL || num_fractions <= 0 || epsilon <= 0) {
        return INVALID_INPUT;
    }
    StatusCode base_status = validate_base(base);
    if (base_status != STATUS_OK) {
        return base_status;
    } 
    const long long PRECISION_POWER = 1000000000;

    va_list args;
    va_start(args, num_fractions);
    for (int i = 0; i < num_fractions; i++) {
        double curr = va_arg(args, double);
        StatusCode frac_status = validate_fraction(curr, epsilon);
        if (frac_status != STATUS_OK) {
            va_end(args);
            return INVALID_INPUT;
        }

        long long num = (long long)round(curr * (long double)PRECISION_POWER);
        long long denom = PRECISION_POWER;
        bool is_fin;
        StatusCode check_status = is_finite(base, num, denom, &is_fin);
        if (check_status != STATUS_OK) {
            va_end(args);
            return check_status;
        }
        result_buffer[i] = is_fin;
    }
    va_end(args);
    return STATUS_OK;
}