#ifndef CONVERTER_H
#define CONVERTER_H
#include "status_codes.h"
#include <stdbool.h>

void int_to_str(long long num, int base, char* buffer, int max_len);

StatusCode str_to_int(const char* str, int base, long long* result);

bool is_valid_number(const char* str, int base);

StatusCode find_max_abs(const char* inputs[], int count, int base, long long* max_value);

#endif

