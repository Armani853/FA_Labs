#include "../include/functions.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void run_result(const double epsilon, const int max_iter) {
    printf("Запуск набора тестов");
    {
        const int base = 10;
        const double ex_fractions[] = {1.0 / 4.0, 1.0 / 5.0, 1.0 / 11.0, 1.0 / 2.0, 4.0 / 5.0};
        const int count = 5;
        bool results[count];

        StatusCode s = check_finite(base, epsilon, max_iter, &results[0], count, ex_fractions[0], ex_fractions[1], ex_fractions[2], ex_fractions[3], ex_fractions[4]);
        printf("\nТест 1: Основание: 10\n");
        print_status(s);
        const bool expected[] = {true, true, false, true, true};
        bool flag = true;
        for (int i = 0; i < count; i++) {
            if (results[i] != expected[i]) {
                flag = false;
            }
        }
        if (flag) {
            printf("Сравнение прошло успешно\n");
        } else {
            printf("Сравнение прошло неуспешно\n");
            print_res(base, epsilon, count, ex_fractions, results);
        }
    }

    {
        const int base = 4;
        const double ex_fractions[] = {1.0 / 2.0, 1.0 / 10.0, 1.0 / 4.0, 1.0 / 5.0};
        const int count = 4;
        bool results[count];
        StatusCode s = check_finite(base, epsilon, max_iter, results, count, ex_fractions[0], ex_fractions[1], ex_fractions[2], ex_fractions[3]);
        printf("Тест 2 Основание: 4\n");
        print_status(s);
        const bool expected[] = {true, false, true, false};
        bool flag = true;
        for (int i = 0; i < count; i++) {
            if (results[i] != expected[i]) {
                flag = false;
            }
        }
        if (flag) {
            printf("Сравнение прошло успешно\n");
        } else {
            printf("Сравнение прошло неуспешно\n");
            print_res(base, epsilon, count, ex_fractions, &results[0]);
        }
    }
    
}


int main() {
    const int base = 3;
    const int num_fractions = 4;
    bool results[num_fractions];
    const double frac1 = 1.0 / 2.0;
    const double frac2 = 1.0 / 3.0;
    const double frac3 = 6.0 / 10.0;
    const double frac4 = 1.0 / 11.0;
    run_result(EPS, MAX_ITER);
    StatusCode s = check_finite(base, EPS, MAX_ITER, results, num_fractions, frac1, frac2, frac3, frac4);
    if (s == STATUS_OK) {
        const double fractions[] = {frac1, frac2, frac3, frac4};
        print_res(base, EPS, num_fractions, fractions, &results[0]);
    }
    return 0;
}