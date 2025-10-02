#include "converter.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MAX_DIGITS 64

bool is_valid_digit(char c, int base) {
    if (c >= '0' && c <= '9') {
        return (c - '0') < base;
    }
    if (c >= 'A' && c <= 'Z') {
        return (c - 'A' + 10) < base;
    }
    return false;
}

bool is_valid_number(const char* str, int base) {
    if (!str || !*str) {
        return false;
    }
    int i = 0;
    if (str[0] == '-' || str[0] == '+') {
        i = 1;
    }

    if (str[i] == '\0') {
        return false;
    }
    
    for (; str[i]; i++) {
        if (!is_valid_digit(str[i], base)) {
            return false;
        }
    }
    return true;
}

StatusCode str_to_int(const char* str, int base, long long* result) {
    if (!str || !result || !*str) {
        return INVALID_INPUT;
    }
    char* endptr;
    long long val = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    } else if (str[0] == '+') {
        i = 1;
    }
    if (str[i] == '\0') {
        return INVALID_INPUT;
    }
    for (; str[i]; i++) {
        char c = str[i];
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            return INVALID_INPUT;
        }
        if (digit >= base) {
            return INVALID_INPUT;
        }
        if (val > (LLONG_MAX - digit) / base ) {
            return OVERFLOW_ERROR;
        }
        val = val * base + digit;
    }
    *result = sign * val;
    return STATUS_OK;
}

void int_to_str(long long num, int base, char* buffer, int max_len) {
    if (num == 0) {
        strncpy(buffer, "0", max_len);
        buffer[max_len - 1] = '\0';
        return;
    }

    char temp[MAX_DIGITS];
    int i = 0;
    bool negative = num < 0;
    if (negative) {
        num = -num;
    } 
    while (num > 0) {
        int r = num % base;
        temp[i++] = (r < 10) ? ('0' + r) : ('A' + r - 10);
        num /= base;
    }
    if (negative) {
        temp[i++] = '-';
    }
    for (int j = 0; j < i; j++) {
        buffer[j] = temp[i - 1 - j];
    }
    buffer[i] = '\0';
    if (i >= max_len) {
        buffer[max_len - 1] = '\0';
    }
}

StatusCode find_max_abs(const char* inputs[], int count, int base, long long* max_value) {
    if (count == 0) {
        return INVALID_INPUT;
    }
    long long current;
    bool first = true;
    for (int i = 0; i < count; i++) {
        StatusCode status = str_to_int(inputs[i], base, &current);
        if (status != STATUS_OK) {
            continue;
        }
        if (first || llabs(current) > llabs(*max_value)) {
            *max_value = current;
            first = false;
        }
    }
    return first ? INVALID_INPUT : STATUS_OK;
}