#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "status_codes.h"
#define MAX_FIB 1000000

int overfscanf(FILE *stream, const char *format, ...);
int oversscanf(const char *str, const char *format, ...);

int roman_to_int(const char *str, int *result);
int zeckendorf_to_uint(const char *str, unsigned int *result);
int scan_custom_base(const char **str, int *result, int base, int uppercase);

int is_roman_char(char c);

int generate_fibonacci(unsigned int n, unsigned int **fib_sequence, int *size);

int skip_whitespace_stream(FILE *stream);

int skip_whitespace_string(const char **str);

int process_specifier(const char **format, va_list *args, 
                            FILE *stream, const char **str_input, int *success_count);