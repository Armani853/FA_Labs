#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
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
        case CALCULATION_ERROR:
            printf("Ошибка в вычислениях\n");
            break;
        default:
            printf("Неивестная ошибка");
    }
}

StatusCode validate_arguments(int argc, char* argv[], double* epsilon) {
    if (argc != 2) {
        print_error(INVALID_INPUT);
        return INVALID_INPUT;
    }
    char* endptr;
    *epsilon = strtod(argv[1], &endptr);
    if (endptr == argv[1] || *endptr != '\0') {
        print_error(INVALID_INPUT);
        return INVALID_INPUT;
    }
    if (IS_LESS_OR_EQUAL(*epsilon, 0, *epsilon) || IS_MORE_OR_EQUAL(*epsilon, 1, *epsilon)) {
        print_error(CALCULATION_ERROR);
        return CALCULATION_ERROR;
    }
    return STATUS_OK;
}

double integral_a(double x) {
    if (x == 0.0) return 1.0;
    return log((1.0 + x)) / x;
}

double integral_b(double x) {
    return exp(-(x * x) / 2.0);
}

double integral_c(double x) {
    if (x == 0.0) return 0.0;  
    return log(1.0 / (1.0 - x));
}

double integral_d(double x) {
    if (x == 0.0) return 1.0; 
    return pow(x, x);
}

StatusCode calc(double (*func)(double), double a, double b, double epsilon, double* result, int* iterations) {
    if (func == NULL || result == NULL || iterations == NULL) {
        print_error(INVALID_INPUT);
        return INVALID_INPUT;
    }
    
    if (IS_LESS_OR_EQUAL(epsilon, 0, epsilon) || IS_MORE_OR_EQUAL(epsilon, 1, epsilon)) {
        print_error(CALCULATION_ERROR);
        return CALCULATION_ERROR;
    }
    
    if (IS_LESS_OR_EQUAL(b, a, epsilon)) {
        print_error(INVALID_INPUT);
        return INVALID_INPUT;
    }
    
    size_t n = 2;  
    const size_t MAX_ITERATIONS = 1000000;
    double prev_result = 0.0;
    double current_result = 0.0;
    double difference = 0.0;
    
    double h = (b - a) / n;
    current_result = 0.5 * (func(a) + func(b));
    for (size_t i = 1; i < n; i++) {
        current_result += func(a + i * h);
    }
    current_result *= h;
    
    do {
        prev_result = current_result;
        n *= 2;
        
        if (n > MAX_ITERATIONS) {
            print_error(CALCULATION_ERROR);
            return CALCULATION_ERROR;
        }
        
        h = (b - a) / n;
        current_result = 0.5 * (func(a) + func(b));
        
        for (size_t i = 1; i < n; i++) {
            current_result += func(a + i * h);
        }
        current_result *= h;
        
        difference = fabs(current_result - prev_result);
    } while (IS_MORE(difference / 3.0, epsilon, epsilon) && n < MAX_ITERATIONS);
    
    *result = current_result;
    *iterations = n;
    
    return STATUS_OK;
}