#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    long T;
    printf("Введите количество запросов: ");
    if (scanf("%ld", &T) != 1 || T < 1 || T > 1000) {
        return INVALID_INPUT;
    }
    for (long i = 0; i < T; i++) {
        long n;
        printf("Введите порядковый номер простого числа: ");
        if (scanf("%ld", &n) != 1) {
            return INVALID_INPUT;
        }
        long result;
        StatusCode status = find_n_prime(n, &result);

        switch (status) {
            case STATUS_OK:
                printf("Результат: %ld\n", result);
                break;
            case INVALID_INPUT:
                printf("Неверный ввод");
                break;
            case OUT_OF_RANGE:
                printf("Выход за пределы массива");
                break;
            case MEMORY_ERROR:
                printf("Неудачное выделение памяти");
                break;
            default:
                printf("Неизвестная ошибка");
        }

    }
    return 0;
}


