#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include <math.h>
#define IS_ZERO(val, eps) (fabs(val) < eps)
#define IS_EQUAL(fval, sval, eps) (fabs(fval - sval) < eps)
#define IS_MORE(fval, sval, eps) ((fval - sval) > eps)
#define IS_LESS(fval, sval, eps) ((sval - fval) > eps)
#define IS_MORE_OR_EQUAL(fval, sval, eps) ((fval - sval) > -(eps))
#define IS_LESS_OR_EQUAL(fval, sval, eps) ((sval - fval) > -(eps))


void print_error(StatusCode status) {
    switch(status) {
        case STATUS_OK:
            printf("Все завершилось успешно");
            break;
        case INVALID_INPUT:
            printf("Неверный ввод\n");
            break;
        case WRONG_NUMBER_OF_ARGUMENTS:
            printf("Неверное количество аргументов\n");
            break;
        case DIVISION_BY_ZERO:
            printf("Деление на ноль\n");
            break;
        case OVERFLOW_ERROR:
            printf("Переполнение или неверное значение\n");
            break;
        case NO_SOLUTION:
            printf("Нет решения\n");
            break;
        case STATUS_ERROR:
            printf("Неверный статус");
            break;
        default:
            printf("Неивестная ошибка");
    }
}
bool is_double(const char* str) {
    char* endptr;
    double val = strtod(str, &endptr);
    if (*endptr == '\0' && str != endptr) {
        return true;
    } else {
        return false;
    }
}

bool is_int(const char* str) {
    char* endptr;
    long val;
    if (str == NULL || *str == '\0') {
        return false;
    }
    val = strtol(str, &endptr, 10);
    if (*endptr != '\0' || endptr == str) {
        return false;
    } else {
        return true;
    }
}

StatusCode str_to_int(const char* str, long* result) {
    char* endptr;
    if (str == NULL || *str == '\0') {
        return INVALID_INPUT;
    }
    long val = strtol(str, &endptr, 10);
    if (*endptr != '\0' || str == endptr) {
        return INVALID_INPUT;
    }
    *result = val;
    return STATUS_OK;
}

StatusCode str_to_double(const char* const str, double* result) {
    char* endptr;
    if (!str || !result) {
        return INVALID_INPUT;
    }
    double val = strtod(str, &endptr);
    if (*endptr != '\0') {
        return INVALID_INPUT;
    }
    if (isinf(val) || isnan(val)) {
        return OVERFLOW_ERROR;
    }
    *result = val;
    return STATUS_OK;
}

StatusCode quad_solve(double a, double b, double c, double epsilon, 
                           double *r1, double *r2, int *num_roots) {
    
    if (IS_LESS_OR_EQUAL(epsilon, 0, epsilon)) {
        return INVALID_INPUT;
    }
    if (isnan(a) || isinf(a) || isnan(b) || isinf(b) || isnan(c) || isinf(c)) {
        return OVERFLOW_ERROR;
    }
    
    if (IS_ZERO(a, epsilon)) {
        if (IS_ZERO(b, epsilon)) {
            if (IS_ZERO(c, epsilon)) {
                *num_roots = -1;
            } else {
                *num_roots = 0;
            }
        } else {
            *num_roots = 1;
            *r1 = -c / b;
            *r2 = *r1;
        }
        return STATUS_OK;
    }

    double D = b * b - 4 * a * c;
    
    if (IS_ZERO(D, epsilon)) {
        *num_roots = 1;
        *r1 = -b / (2 * a);
    } else if (D > 0) {
        *num_roots = 2;
        *r1 = (-b + sqrt(D)) / (2 * a);
        *r2 = (-b - sqrt(D)) / (2 * a);
    } else {
        *num_roots = 0;
    }
    return STATUS_OK;
}

StatusCode check_mul(long long m, long long n, bool *is_multiple) {
    if (n == 0) {
        return DIVISION_BY_ZERO;
    }    
    *is_multiple = (m % n == 0); 
    return STATUS_OK;
}

StatusCode handle_flag_q(int argc, char* argv[]) {
    if (argc != 6) {
        return WRONG_NUMBER_OF_ARGUMENTS;
    }
    double epsilon, coeffs[3];
    StatusCode status;
    if ((status = str_to_double(argv[2], &epsilon)) != STATUS_OK) {
        print_error(status);
        return status;
    }
    if (epsilon <= 0) {
        print_error(INVALID_INPUT);
        return INVALID_INPUT;
    }
    for (int i = 0; i < 3; i++) {
        if ((status = str_to_double(argv[3 + i], &coeffs[i])) != STATUS_OK) {
            print_error(status);
            return status;
        }
    }
    const int p[6][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

    printf("Флаг -q: Решения квадратного уравнения Ax^2 + Bx + C = 0:\n");

    for (int i = 0; i < 6; i++) {
        double a = coeffs[p[i][0]];
        double b = coeffs[p[i][1]];
        double c = coeffs[p[i][2]];
        
        double r1 = 0, r2 = 0;
        int num_roots = 0;
        
        status = quad_solve(a, b, c, epsilon, &r1, &r2, &num_roots);
        
        printf(" (A=%.4f, B=%.4f, C=%.4f): ", a, b, c);

        switch (status) {
            case STATUS_OK:
                if (num_roots == 2) {
                    printf("Два корня: x1=%.4f, x2=%.4f\n", r1, r2);
                } else if (num_roots == 1) {
                    printf("Один корень: x=%.4f\n", r1);
                } else if (num_roots == 0) {
                    printf("Нет действительных корней.\n");
                } else { 
                    printf("Бесконечно много решений.\n");
                }
                break;
            default:
                printf("Ошибка при вычислении (Код: %d).\n", status);
        }
    }
}

StatusCode check_right_triangle(double s1, double s2, double s3, double epsilon, bool *is_right) {
    if (IS_LESS_OR_EQUAL(s1, 0, epsilon) || IS_LESS_OR_EQUAL(s2, 0, epsilon) || IS_LESS_OR_EQUAL(s3, 0, epsilon)) {
        return INVALID_INPUT;
    }

    if (IS_LESS_OR_EQUAL(s1 + s2, s3, epsilon) || IS_LESS_OR_EQUAL(s1 + s3, s2, epsilon) || IS_LESS_OR_EQUAL(s2 + s3, s1, epsilon)) {
        *is_right = false;
        return STATUS_OK; 
    }

    double max_side = fmax(s1, fmax(s2, s3));
    double a, b, c = max_side;

    if (IS_EQUAL(max_side, s1, epsilon)){
        a = s2;
        b = s3;
    } else if (IS_EQUAL(max_side, s2, epsilon)) {
         a = s1;
         b = s3;
    } else {
         a = s1;
         b = s2;
    }

    *is_right = IS_EQUAL(a * a + b * b, c * c, epsilon);
    return STATUS_OK;
}