#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdarg.h>

#define EPS 1.0e-12
#define IS_EQUAL(fval, sval, eps) (fabs((fval) - (sval)) < (eps))
#define IS_MORE_OR_EQUAL(fval, sval, eps) (((fval) - (sval)) > -(eps))
#define IS_LESS_OR_EQUAL(fval, sval, eps) (((sval) - (fval)) > -(eps))

typedef enum {
    STATUS_OK = 0,
    INVALID_INPUT,
} StatusCode;

StatusCode validate_base(const int base);
StatusCode validate_fraction(const double fraction, const double epsilon);

StatusCode check_finite(const int base, const double epsilon, bool* result_buffer, const int num_fractions, ...);

void test_validate_base() {
    assert(validate_base(2) == STATUS_OK);
    printf("Test base 2 OK\n");
    assert(validate_base(10) == STATUS_OK);
    printf("Test base 10 OK\n");
    assert(validate_base(1) == INVALID_INPUT);
    printf("Test base 1 invalid OK\n");
    assert(validate_base(0) == INVALID_INPUT);
    printf("Test base 0 invalid OK\n");
    assert(validate_base(-5) == INVALID_INPUT);
    printf("Test base -5 invalid OK\n");
}

void test_validate_fraction() {
    assert(validate_fraction(0.5, EPS) == STATUS_OK);
    printf("Test frac 0.5 OK\n");
    assert(validate_fraction(0.0001, EPS) == STATUS_OK);
    printf("Test frac 0.0001 OK\n");
    assert(validate_fraction(0.9999, EPS) == STATUS_OK);
    printf("Test frac 0.9999 OK\n");
    
    assert(validate_fraction(0.0, EPS) == INVALID_INPUT);
    printf("Test frac 0.0 invalid OK\n");
    assert(validate_fraction(1.0, EPS) == INVALID_INPUT);
    printf("Test frac 1.0 invalid OK\n");
    assert(validate_fraction(1.0 + EPS, EPS) == INVALID_INPUT);
    printf("Test frac > 1.0 invalid OK\n");
    assert(validate_fraction(-0.1, EPS) == INVALID_INPUT);
    printf("Test frac -0.1 invalid OK\n");
}

void test_check_finite_basic() {
    bool results[2];
    
    StatusCode s1 = check_finite(10, EPS, results, 1, 1.0 / 4.0);
    assert(s1 == STATUS_OK);
    assert(results[0] == true);
    printf("Test 1/4 in B=10 (Finite) OK\n");
    
    StatusCode s2 = check_finite(10, EPS, results, 1, 1.0 / 3.0);
    assert(s2 == STATUS_OK);
    printf("Test 1/3 in B=10 (Infinite) OK\n");

    StatusCode s3 = check_finite(3, EPS, results, 1, 1.0 / 3.0);
    assert(s3 == STATUS_OK);
    printf("Test 1/3 in B=3 (Finite) OK\n");
    
    StatusCode s4 = check_finite(3, EPS, results, 1, 1.0 / 2.0);
    assert(s4 == STATUS_OK);
    assert(results[0] == false);
    printf("Test 1/2 in B=3 (Infinite) OK\n");
}

void test_check_finite_errors() {
    bool results[2];
    
    StatusCode s1 = check_finite(1, EPS, results, 1, 0.5);
    assert(s1 == INVALID_INPUT);
    printf("Test check_finite invalid base OK\n");
    
    StatusCode s2 = check_finite(10, EPS, results, 1, 1.0);
    assert(s2 == INVALID_INPUT);
    printf("Test check_finite invalid fraction OK\n");

    StatusCode s3 = check_finite(10, EPS, results, 0);
    assert(s3 == INVALID_INPUT);
    printf("Test check_finite zero fractions OK\n");

    StatusCode s4 = check_finite(10, EPS, NULL, 1, 0.5);
    assert(s4 == INVALID_INPUT);
    printf("Test check_finite NULL buffer OK\n");
}

void test_main() {
    printf("--- Запуск тестов Assert ---\n");
    test_validate_base();
    test_validate_fraction();
    test_check_finite_basic();
    test_check_finite_errors();
    printf("Все тесты успешно пройдены!\n");
}

int main() {
    test_main();
    return 0;
}