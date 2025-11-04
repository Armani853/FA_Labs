#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "status_codes.h"
#define MAX_BUFFER_SIZE 1024
#define MAX_ROMAN_LENGTH 20
#define MAX_ZEK_LENGTH 100
#define MAX_BASE_CONVERSION_LENGTH 65
#define BINARY_BYTE_LENGTH 9
#define FLOAT_BYTES 4
#define DOUBLE_BYTES 8
#define INT_BYTES 4


int overfprintf(FILE* stream, const char* format, ...);
int oversprintf(char* str, const char* format, ...);

int overprintf_core(void (*output_func)(char, void*), void* context, 
                   const char* format, va_list args);

StatusCode int_to_roman(int number, char* buffer, size_t buffer_size);
StatusCode roman_to_int(const char* roman, int* result);
int roman_char_to_value(char c);


int is_valid_roman(const char* roman);


StatusCode uint_to_zeckendorf(unsigned int number, char* buffer, size_t buffer_size);
StatusCode zeckendorf_to_uint(const char* zeck, unsigned int* result);

StatusCode generate_fibonacci(unsigned int max, unsigned int** fib_sequence, size_t* count);


StatusCode int_to_base(int number, int base, char* buffer, 
                     size_t buffer_size, int uppercase);
StatusCode base_to_int(const char* str, int base, int* result, int uppercase);
int is_valid_base(int base);


StatusCode memory_dump_int(int value, char* buffer, size_t buffer_size);
StatusCode memory_dump_uint(unsigned int value, char* buffer, size_t buffer_size);
StatusCode memory_dump_double(double value, char* buffer, size_t buffer_size);
StatusCode memory_dump_float(float value, char* buffer, size_t buffer_size);

StatusCode byte_to_binary(unsigned char byte, char* buffer, size_t buffer_size);


typedef struct {
    int value;
    const char* numeral;
} RomanNumeral;


typedef struct {
    FILE* stream; 
    char* buffer;    
    size_t size;      
    size_t pos;  
} OutputContext;