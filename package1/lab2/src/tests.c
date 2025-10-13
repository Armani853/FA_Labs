#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "functions.h"

int check_status(StatusCode actual, StatusCode expected, const char* test_name) {
    if (actual == expected) {
        printf("[PASSED] %s\n", test_name);
        return 1;
    } else {
        fprintf(stderr, "[FAILED] %s: Expected status %d, got %d\n", 
                test_name, expected, actual);
        assert(actual == expected);
        return 0;
    }
}


void run_tests() {
    printf("Запуск тестов\n");
    printf("===========================================\n");
    
    printf("--- Тесты is_prime ---\n");
    
    assert(is_prime(17) == STATUS_OK);
    printf("[PASSED] is_prime: x = 17 (Простое)\n");
    
    assert(is_prime(18) == NOT_PRIME);
    printf("[PASSED] is_prime: x = 18 (Составное)\n");

    assert(is_prime(49) == NOT_PRIME);
    printf("[PASSED] is_prime: x = 49 (Составное)\n");
    
    assert(is_prime(2) == STATUS_OK);
    printf("[PASSED] is_prime: x = 2 (Крайний случай)\n");

    assert(is_prime(1) == INVALID_INPUT);
    printf("[PASSED] is_prime: x = 1 (INVALID_INPUT)\n");

    assert(is_prime(-5) == INVALID_INPUT);
    printf("[PASSED] is_prime: x = -5 (INVALID_INPUT)\n");


    printf("\n--- Тесты find_n_prime ---\n");
    long result;
    StatusCode status;
    
    status = find_n_prime(1, &result);
    assert(status == STATUS_OK && result == 2);
    printf("[PASSED] find_n_prime: n = 1 (Результат: 2)\n");

    status = find_n_prime(5, &result);
    assert(status == STATUS_OK && result == 11);
    printf("[PASSED] find_n_prime: n = 5 (Результат: 11)\n");

    status = find_n_prime(10, &result);
    assert(status == STATUS_OK && result == 29);
    printf("[PASSED] find_n_prime: n = 10 (Результат: 29)\n");

    status = find_n_prime(100000, &result);
    assert(status == STATUS_OK);
    printf("[PASSED] find_n_prime: n = 100000 (Проверка статуса)\n");

    status = find_n_prime(0, &result);
    assert(status == INVALID_INPUT);
    printf("[PASSED] find_n_prime: n = 0 (INVALID_INPUT)\n");

    status = find_n_prime(100001, &result);
    assert(status == OUT_OF_RANGE);
    printf("[PASSED] find_n_prime: n = 100001 (OUT_OF_RANGE)\n");
    

    printf("\n===========================================\n");
    printf("ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!\n");
}

int main() {
    run_tests();
    return EXIT_SUCCESS;
}