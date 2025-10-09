#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"
#include "status_codes.h"

int check_status(StatusCode actual, StatusCode expected, const char* test_name) {
    if (actual == expected) {
        printf("[ПРОЙДЕНО] %s\n", test_name);
        return 1;
    } else {
        fprintf(stderr, "[ОШИБКА] %s: Ожидался статус %d, получен %d\n", 
                        test_name, expected, actual);
        assert(actual == expected);
        return 0;
    }
}

int check_bool(bool actual, bool expected, const char* test_name) {
    if (actual == expected) {
        printf("[ПРОЙДЕНО] %s\n", test_name);
        return 1;
    } else {
        fprintf(stderr, "[ОШИБКА] %s: Ожидалось %s, получено %s\n", 
                        test_name, expected ? "истина" : "ложь", actual ? "истина" : "ложь");
        assert(actual == expected);
        return 0;
    }
}


void run_tests() {
    printf("Запуск тестов\n");

    printf("\n--- Тесты преобразования строк ---\n");
    long long_res;
    double double_res;
    StatusCode status;

    status = str_to_int("456", &long_res);
    assert(status == STATUS_OK && long_res == 456);
    printf("[ПРОЙДЕНО] str_to_int: '456' (OK)\n");

    status = str_to_int("12a", &long_res);
    check_status(status, INVALID_INPUT, "str_to_int: '12a' (Неверный формат)");

    status = str_to_double("2.718", &double_res);
    assert(status == STATUS_OK && fabs(double_res - 2.718) < 1e-9);
    printf("[ПРОЙДЕНО] str_to_double: '2.718' (OK)\n");
    
    status = str_to_double("INF", &double_res);
    check_status(status, OVERFLOW_ERROR, "str_to_double: 'INF' (Переполнение)");


    printf("\n--- Тесты кратности (-m) ---\n");
    bool is_mul;

    status = check_mul(15, 5, &is_mul);
    check_status(status, STATUS_OK, "check_mul: 15 / 5 (Статус OK)");
    check_bool(is_mul, true, "check_mul: 15 / 5 (Результат КРАТНО)");

    status = check_mul(16, 5, &is_mul);
    check_status(status, STATUS_OK, "check_mul: 16 / 5 (Статус OK)");
    check_bool(is_mul, false, "check_mul: 16 / 5 (Результат НЕ кратно)");

    status = check_mul(20, 0, &is_mul);
    check_status(status, DIVISION_BY_ZERO, "check_mul: 20 / 0 (Деление на ноль)");
    
    status = check_mul(-12, 3, &is_mul);
    check_status(status, STATUS_OK, "check_mul: -12 / 3 (Отрицательное)");
    check_bool(is_mul, true, "check_mul: -12 / 3 (Результат КРАТНО)");


    printf("\n--- Тесты прямоугольного треугольника (-t) ---\n");
    bool is_right;
    double eps = 1e-6;

    status = check_right_triangle(6.0, 8.0, 10.0, eps, &is_right);
    check_status(status, STATUS_OK, "check_right_triangle: 6, 8, 10 (Статус OK)");
    status = check_right_triangle(10.0, 6.0, 8.0, eps, &is_right);
    check_status(status, STATUS_OK, "check_right_triangle: 10, 6, 8 (Перестановка OK)");    
    status = check_right_triangle(1.0, 2.0, 5.0, eps, &is_right);
    check_status(status, STATUS_OK, "check_right_triangle: 1, 2, 5 (Статус OK)");
    check_bool(is_right, false, "check_right_triangle: 1, 2, 5 (Результат НЕ треугольник)");
    
    status = check_right_triangle(3.0, 4.0, 5.1, 1e-1, &is_right);
    check_status(status, STATUS_OK, "check_right_triangle: 3, 4, 5.1 (Большой eps, НЕ прямоугольный)");
    check_bool(is_right, false, "check_right_triangle: 3, 4, 5.1 (Результат Ложь)");
    
    status = check_right_triangle(3.0, 4.0, 5.000000001, 1e-8, &is_right);
    check_status(status, STATUS_OK, "check_right_triangle: 3, 4, 5.00..1 (Малый eps, НЕ прямоугольный)");
    check_bool(is_right, false, "check_right_triangle: 3, 4, 5.00..1 (Результат Ложь)");
    
    status = check_right_triangle(-1.0, 4.0, 5.0, eps, &is_right);
    check_status(status, INVALID_INPUT, "check_right_triangle: Отрицательная сторона");


    printf("\n--- Тесты квадратного уравнения (-q) ---\n");
    double r1, r2;
    int num_roots;

    status = quad_solve(1.0, 0.0, -9.0, eps, &r1, &r2, &num_roots);
    check_status(status, STATUS_OK, "quad_solve: x^2 - 9 = 0 (Статус OK)");
    assert(num_roots == 2 && fabs(r1 - 3.0) < eps);
    printf("[ПРОЙДЕНО] quad_solve: x^2 - 9 = 0 (2 корня)\n");

    status = quad_solve(1.0, 4.0, 4.0, eps, &r1, &r2, &num_roots);
    check_status(status, STATUS_OK, "quad_solve: x^2 + 4x + 4 = 0 (Статус OK)");
    assert(num_roots == 1 && fabs(r1 - -2.0) < eps);
    printf("[ПРОЙДЕНО] quad_solve: x^2 + 4x + 4 = 0 (1 корень)\n");

    status = quad_solve(1.0, 0.0, 5.0, eps, &r1, &r2, &num_roots);
    check_status(status, STATUS_OK, "quad_solve: x^2 + 5 = 0 (Статус OK)");
    assert(num_roots == 0);
    printf("[ПРОЙДЕНО] quad_solve: x^2 + 5 = 0 (0 корней)\n");

    status = quad_solve(0.0, 3.0, 9.0, eps, &r1, &r2, &num_roots);
    check_status(status, STATUS_OK, "quad_solve: 3x + 9 = 0 (Статус OK)");
    assert(num_roots == 1 && fabs(r1 - -3.0) < eps);
    printf("[ПРОЙДЕНО] quad_solve: 3x + 9 = 0 (Линейное)\n");
    
    status = quad_solve(0.0, 0.0, 0.0, eps, &r1, &r2, &num_roots);
    check_status(status, STATUS_OK, "quad_solve: 0 = 0 (Статус OK)");
    assert(num_roots == -1);
    printf("[ПРОЙДЕНО] quad_solve: 0 = 0 (Бесконечно много)\n");

    
    printf("ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!\n");
}

int main() {
    run_tests();
    return EXIT_SUCCESS;
}