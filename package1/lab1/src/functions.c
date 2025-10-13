#include <stdio.h>
#include "functions.h"
#include <math.h>

StatusCode dividers(int x) {
    if (x <= 0) {
        return INVALID_INPUT;
    }
    int found = 0;
    for (int i = 1; i < 100; i++) {
        if (i % x == 0) {
            printf("%d ", i);
            found = 1;
        }
    }
    if (found) {
        return STATUS_OK;
    } else {
        return NO_NUMBERS;
    }
}

StatusCode is_prime(int x) {
    if (x <= 1) {
        return INVALID_INPUT;
    }
    int is_prime = 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            is_prime = 0;
            printf("Число %d является составным", x);
            return STATUS_OK;
        }
        
    }
    printf("Число %d является простым", x);
    return STATUS_OK;

}

StatusCode divide_hex(int x) {
    if (x < 0) {
        return INVALID_INPUT;
    }
    if (x == 0) {
        printf("0\n");
        return STATUS_OK;
    }
    int temp_x = x;
    char hex_digits[100];
    int i = 0;
    while (temp_x > 0) {
        long rem = temp_x % 16;
        if (rem < 10) {
            hex_digits[i] = rem + '0';
        } else {
            hex_digits[i] = rem + 'A' - 10;
        }
        temp_x /= 16;
        i++;
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", hex_digits[j]);
        if (j > 0) {
            printf(" ");
        }
    }
    printf("\n");
    return STATUS_OK;
}

StatusCode degrees(int x) {
    if (x < 1|| x > 10) {
        return INVALID_INPUT;
    }
    for (int base = 1; base <= 10; base++) {
        for (int exp = 1; exp <= x; exp++) {
            printf("%ld^%d = %.0f\t", (long)base, exp, pow(base, exp));
        }
        printf("\n");
    }
    return STATUS_OK;
}

StatusCode sum(int x) {
    if (x < 1) {
        return INVALID_INPUT;
    }
    int s = x * (x + 1) / 2;
    printf("%d", s);
    return STATUS_OK;
}

StatusCode fac(int x) {
    if (x < 1) {
        return INVALID_INPUT;
    }
    long long fac = 1;
    for (int i = 1; i <= x; i++) {
        fac *= i;
    }
    printf("%lld\n", fac);
    return STATUS_OK;
}

