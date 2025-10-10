#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <float.h>

#define IS_EQUAL(fval, sval, eps) (fabs(fval - sval) < eps)

typedef enum {
    STATUS_OK = 0,
    INVALID_INPUT = 1,
    CALCULATION_ERROR = 2
} StatusCode;

double integral_a(double x);
double integral_b(double x);
double integral_c(double x);
double integral_d(double x);
StatusCode calc(double (*func)(double), double a, double b, double epsilon, double* result, int* iterations);
StatusCode validate_arguments(int argc, char* argv[], double* epsilon);

void test_integral_values() {
    double eps = 1e-4;
    double a, b, c, d;
    int iter;

    assert(calc(integral_b, 0.0, 1.0, 1e-6, &b, &iter) == STATUS_OK);
    assert(IS_EQUAL(b, 0.855624, eps));    
    assert(calc(integral_d, 0.0, 1.0, 1e-6, &d, &iter) == STATUS_OK);
    assert(IS_EQUAL(d, 0.783431, eps));

    printf("Тесты значений интегралов пройдены.\n");
}

void test_argument_validation() {
    double eps;
    char* argv_ok[] = {"./test", "0.001"};
    char* argv_zero[] = {"./test", "0"};
    char* argv_big[] = {"./test", "1.0"};
    char* argv_word[] = {"./test", "abc"};
    char* argv_few[] = {"./test"};

    assert(validate_arguments(2, argv_ok, &eps) == STATUS_OK);
    assert(validate_arguments(2, argv_word, &eps) == INVALID_INPUT);
    assert(validate_arguments(1, argv_few, &eps) == INVALID_INPUT);

    printf("Тесты валидации аргументов пройдены.\n");
}

void test_calc_validation() {
    double res;
    int iter = 0;
    
    assert(calc(integral_b, 0.0, 1.0, 1e-3, NULL, &iter) == INVALID_INPUT);
    assert(calc(NULL, 0.0, 1.0, 1e-3, &res, &iter) == INVALID_INPUT);

    assert(calc(integral_b, 1.0, 1.0, 1e-3, &res, &iter) == INVALID_INPUT);
    assert(calc(integral_b, 2.0, 1.0, 1e-3, &res, &iter) == INVALID_INPUT);
    
    assert(calc(integral_b, 0.0, 1.0, 0.0, &res, &iter) == CALCULATION_ERROR);
    assert(calc(integral_b, 0.0, 1.0, 1.0, &res, &iter) == CALCULATION_ERROR);

    printf("Тесты валидации calc пройдены.\n");
}

int main() {
    printf("--- Запуск тестов ---\n");
    test_argument_validation();
    test_calc_validation();
    test_integral_values();
    printf("--- Все тесты успешно завершены. ---\n");
    return 0;
}