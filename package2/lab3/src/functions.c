#include "../include/functions.h"



const RomanNumeral roman_numerals[] = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"},  {90, "XC"},  {50, "L"},  {40, "XL"},
    {10, "X"},   {9, "IX"},   {5, "V"},   {4, "IV"},
    {1, "I"}
};

const size_t roman_numerals_count = 
    sizeof(roman_numerals) / sizeof(roman_numerals[0]);

StatusCode int_to_roman(int number, char* buffer, size_t buffer_size) {
    if (!buffer || buffer_size == 0) {
        return INVALID_INPUT;
    }
    
    if (number <= 0 || number > 3999) {
        return INVALID_INPUT;
    }
    
    buffer[0] = '\0';
    size_t pos = 0;
    int temp = number;
    
    for (size_t i = 0; i < roman_numerals_count; i++) {
        while (temp >= roman_numerals[i].value) {
            const char* numeral = roman_numerals[i].numeral;
            size_t numeral_len = strlen(numeral);
            
            if (pos + numeral_len >= buffer_size - 1) {
                return OVERFLOW_ERROR;
            }
            
            strcpy(buffer + pos, numeral);
            pos += numeral_len;
            temp -= roman_numerals[i].value;
        }
    }
    
    return STATUS_OK;
}

StatusCode roman_to_int(const char* roman, int* result) {
    if (!roman || !result) {
        return INVALID_INPUT;
    }
    
    if (!is_valid_roman(roman)) {
        return INVALID_INPUT;
    }
    
    *result = 0;
    size_t len = strlen(roman);
    
    for (size_t i = 0; i < len; i++) {
        int current = roman_char_to_value(roman[i]);
        int next = (i + 1 < len) ? roman_char_to_value(roman[i + 1]) : 0;
        
        if (current < next) {
            *result += (next - current);
            i++;  
        } else {
            *result += current;
        }
    }
    
    return STATUS_OK;
}

int roman_char_to_value(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

int is_valid_roman(const char* roman) {
    if (!roman) return 0;
    
    for (size_t i = 0; roman[i] != '\0'; i++) {
        if (!strchr("IVXLCDM", roman[i])) {
            return 0;
        }
    }
    
    return 1;
}


StatusCode generate_fibonacci(unsigned int max, unsigned int** fib_sequence, size_t* count) {
    if (!fib_sequence || !count) {
        return INVALID_INPUT;
    }
    
    if (max == 0) {
        *count = 0;
        *fib_sequence = NULL;
        return STATUS_OK;
    }
    size_t capacity = 10;
    unsigned int* fib = (unsigned int*)malloc(capacity * sizeof(unsigned int));
    if (!fib) {
        return MEMORY_ERROR;
    }
    
    fib[0] = 1;
    fib[1] = 2;
    size_t fib_count = 2;
    
    while (1) {
        unsigned int next = fib[fib_count - 1] + fib[fib_count - 2];
        if (next > max || next < fib[fib_count - 1]) { 
            break;
        }
        
        if (fib_count >= capacity) {
            capacity *= 2;
            unsigned int* new_fib = (unsigned int*)realloc(fib, capacity * sizeof(unsigned int));
            if (!new_fib) {
                free(fib);
                return MEMORY_ERROR;
            }
            fib = new_fib;
        }
        
        fib[fib_count++] = next;
    }
    
    *fib_sequence = fib;
    *count = fib_count;
    return STATUS_OK;
}

StatusCode uint_to_zeckendorf(unsigned int number, char* buffer, size_t buffer_size) {
    if (!buffer || buffer_size == 0) {
        return INVALID_INPUT;
    }
    
    if (number == 0) {
        if (buffer_size < 3) return OVERFLOW_ERROR;
        strcpy(buffer, "01"); 
        return STATUS_OK;
    }
    
    unsigned int* fib = NULL;
    size_t fib_count = 0;
    StatusCode result = generate_fibonacci(number, &fib, &fib_count);
    if (result != STATUS_OK) {
        return result;
    }
    
    char temp_buffer[MAX_ZEK_LENGTH] = {0};
    size_t pos = 0;
    unsigned int temp = number;
    
    for (int i = (int)fib_count - 1; i >= 0; i--) {
        if (temp >= fib[i]) {
            if (pos >= MAX_ZEK_LENGTH - 1) {
                free(fib);
                return OVERFLOW_ERROR;
            }
            temp_buffer[pos++] = '1';
            temp -= fib[i];
        } else {
            if (pos >= MAX_ZEK_LENGTH - 1) {
                free(fib);
                return OVERFLOW_ERROR;
            }
            temp_buffer[pos++] = '0';
        }
    }
    
    if (pos >= MAX_ZEK_LENGTH - 1) {
        free(fib);
        return OVERFLOW_ERROR;
    }
    temp_buffer[pos++] = '1';
    temp_buffer[pos] = '\0';
    
    if (strlen(temp_buffer) >= buffer_size) {
        free(fib);
        return OVERFLOW_ERROR;
    }
    strcpy(buffer, temp_buffer);
    
    free(fib);
    return STATUS_OK;
}


int is_valid_base(int base) {
    return base >= 2 && base <= 36;
}

StatusCode int_to_base(int number, int base, char* buffer, 
                     size_t buffer_size, int uppercase) {
    if (!buffer || buffer_size == 0) {
        return INVALID_INPUT;
    }
    
    if (!is_valid_base(base)) {
        base = 10; 
    }
    
    if (buffer_size < 2) {
        return OVERFLOW_ERROR;
    }
    

    int is_negative = 0;
    unsigned int n;
    
    if (number < 0 && base == 10) {
        is_negative = 1;
        n = -number;
    } else {
        n = (unsigned int)number;
    }
    
    char temp_buffer[MAX_BASE_CONVERSION_LENGTH];
    size_t pos = MAX_BASE_CONVERSION_LENGTH - 1;
    temp_buffer[pos] = '\0';
    
    if (n == 0) {
        temp_buffer[--pos] = '0';
    } else {
        while (n > 0) {
            unsigned int digit = n % base;
            char c;
            
            if (digit < 10) {
                c = '0' + digit;
            } else {
                c = (uppercase ? 'A' : 'a') + (digit - 10);
            }
            
            temp_buffer[--pos] = c;
            n /= base;
        }
    }
    
    if (is_negative) {
        temp_buffer[--pos] = '-';
    }
    
    const char* result_str = temp_buffer + pos;
    size_t result_len = strlen(result_str);
    
    if (result_len >= buffer_size) {
        return OVERFLOW_ERROR;
    }
    
    strcpy(buffer, result_str);
    return STATUS_OK;
}

StatusCode base_to_int(const char* str, int base, int* result, int uppercase) {
    if (!str || !result) {
        return INVALID_INPUT;
    }
    
    if (!is_valid_base(base)) {
        base = 10;
    }
    
    while (*str == ' ') str++;
    
    int is_negative = 0;
    if (*str == '-') {
        is_negative = 1;
        str++;
    } else if (*str == '+') {
        str++;
    }
    
    if (*str == '\0') {
        return INVALID_INPUT;
    }
    
    unsigned int value = 0;
    
    while (*str != '\0') {
        char c = *str;
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'z') {
            if (uppercase) {
                return INVALID_INPUT;
            }
            digit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'Z') {
            if (!uppercase) {
                return INVALID_INPUT;
            }
            digit = c - 'A' + 10;
        } else {
            return INVALID_INPUT;
        }
        
        if (digit >= base) {
            return INVALID_INPUT;
        }
        
        if (value > (UINT_MAX - digit) / base) {
            return INVALID_INPUT;
        }
        
        value = value * base + digit;
        str++;
    }
    
    *result = is_negative ? -(int)value : (int)value;
    return STATUS_OK;
}

StatusCode byte_to_binary(unsigned char byte, char* buffer, size_t buffer_size) {
    if (!buffer || buffer_size < BINARY_BYTE_LENGTH) {
        return OVERFLOW_ERROR;
    }
    
    for (int i = 7; i >= 0; i--) {
        buffer[7 - i] = (byte & (1 << i)) ? '1' : '0';
    }
    buffer[8] = '\0';
    
    return STATUS_OK;
}

StatusCode memory_dump_int(int value, char* buffer, size_t buffer_size) {
    if (!buffer) {
        return INVALID_INPUT;
    }
    
    if (buffer_size < 4 * BINARY_BYTE_LENGTH + 3) {
        return OVERFLOW_ERROR;
    }
    
    unsigned char* bytes = (unsigned char*)&value;
    char temp[BINARY_BYTE_LENGTH];
    size_t pos = 0;
    
    for (int i = 0; i < INT_BYTES; i++) {
        byte_to_binary(bytes[i], temp, sizeof(temp));
        
        strcpy(buffer + pos, temp);
        pos += 8;
        
        if (i < INT_BYTES - 1) {
            buffer[pos++] = ' ';
        }
    }
    
    buffer[pos] = '\0';
    return STATUS_OK;
}

StatusCode memory_dump_uint(unsigned int value, char* buffer, size_t buffer_size) {
    return memory_dump_int(*(int*)&value, buffer, buffer_size);
}

StatusCode memory_dump_float(float value, char* buffer, size_t buffer_size) {
    if (!buffer) {
        return INVALID_INPUT;
    }
    
    if (buffer_size < FLOAT_BYTES * BINARY_BYTE_LENGTH + 3) {
        return OVERFLOW_ERROR;
    }
    
    unsigned char* bytes = (unsigned char*)&value;
    char temp[BINARY_BYTE_LENGTH];
    size_t pos = 0;
    
    for (int i = 0; i < FLOAT_BYTES; i++) {
        byte_to_binary(bytes[i], temp, sizeof(temp));
        strcpy(buffer + pos, temp);
        pos += 8;
        
        if (i < FLOAT_BYTES - 1) {
            buffer[pos++] = ' ';
        }
    }
    
    buffer[pos] = '\0';
    return STATUS_OK;
}

StatusCode memory_dump_double(double value, char* buffer, size_t buffer_size) {
    if (!buffer) {
        return INVALID_INPUT;
    }
    
    if (buffer_size < DOUBLE_BYTES * BINARY_BYTE_LENGTH + 7) {
        return OVERFLOW_ERROR;
    }
    
    unsigned char* bytes = (unsigned char*)&value;
    char temp[BINARY_BYTE_LENGTH];
    size_t pos = 0;
    
    for (int i = 0; i < DOUBLE_BYTES; i++) {
        byte_to_binary(bytes[i], temp, sizeof(temp));
        strcpy(buffer + pos, temp);
        pos += 8;
        
        if (i < DOUBLE_BYTES - 1) {
            buffer[pos++] = ' ';
        }
    }
    
    buffer[pos] = '\0';
    return STATUS_OK;
}




void stream_output(char c, void* context) {
    OutputContext* ctx = (OutputContext*)context;
    if (ctx->stream) {
        fputc(c, ctx->stream);
    }
}

void buffer_output(char c, void* context) {
    OutputContext* ctx = (OutputContext*)context;
    if (ctx->buffer && ctx->pos < ctx->size - 1) {
        ctx->buffer[ctx->pos++] = c;
    }
}

int handle_special_format(void (*output)(char, void*), void* context,
                                const char** format, va_list* args) {
    const char* fmt = *format;
    
    if (strncmp(fmt, "%Ro", 3) == 0) {
        int value = va_arg(*args, int);
        char buffer[MAX_ROMAN_LENGTH];
        
        if (int_to_roman(value, buffer, sizeof(buffer)) == STATUS_OK) {
            for (const char* p = buffer; *p; p++) {
                output(*p, context);
            }
        }
        *format += 2;
        return 1;
    }
    else if (strncmp(fmt, "%Zr", 3) == 0) {
        unsigned int value = va_arg(*args, unsigned int);
        char buffer[MAX_ZEK_LENGTH];
        
        if (uint_to_zeckendorf(value, buffer, sizeof(buffer)) == STATUS_OK) {
            for (const char* p = buffer; *p; p++) {
                output(*p, context);
            }
        }
        *format += 2;
        return 1;
    }
    else if (strncmp(fmt, "%Cv", 3) == 0) {
        int value = va_arg(*args, int);
        int base = va_arg(*args, int);
        char buffer[MAX_BASE_CONVERSION_LENGTH];
        
        if (int_to_base(value, base, buffer, sizeof(buffer), 0) == STATUS_OK) {
            for (const char* p = buffer; *p; p++) {
                output(*p, context);
            }
        }
        *format += 2;
        return 1;
    }
    else if (strncmp(fmt, "%CV", 3) == 0) {
        int value = va_arg(*args, int);
        int base = va_arg(*args, int);
        char buffer[MAX_BASE_CONVERSION_LENGTH];
        
        if (int_to_base(value, base, buffer, sizeof(buffer), 1) == STATUS_OK) {
            for (const char* p = buffer; *p; p++) {
                output(*p, context);
            }
        }
        *format += 2;
        return 1;
    }
    else if (strncmp(fmt, "%to", 3) == 0) {
        char* str = va_arg(*args, char*);
        int base = va_arg(*args, int);
        int value;
        
        if (base_to_int(str, base, &value, 0) == STATUS_OK) {
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "%d", value);
            for (const char* p = buffer; *p; p++) {
                output(*p, context);
            }
        }
        *format += 2;
        return 1;
    }
    else if (strncmp(fmt, "%TO", 3) == 0) {
        char* str = va_arg(*args, char*);
        int base = va_arg(*args, int);
        int value;
        
        if (base_to_int(str, base, &value, 1) == STATUS_OK) {
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "%d", value);
            for (const char* p = buffer; *p; p++) {
                output(*p, context);
            }
        }
        *format += 2;
        return 1;
    }
    else if (strncmp(fmt, "%mi", 3) == 0) {
        int value = va_arg(*args, int);
        char buffer[256];
        
        if (memory_dump_int(value, buffer, sizeof(buffer)) == STATUS_OK) {
            for (const char* p = buffer; *p; p++) {
                output(*p, context);
            }
        }
        *format += 2;
        return 1;
    }
    else if (strncmp(fmt, "%mu", 3) == 0) {
        unsigned int value = va_arg(*args, unsigned int);
        char buffer[256];
        
        if (memory_dump_uint(value, buffer, sizeof(buffer)) == STATUS_OK) {
            for (const char* p = buffer; *p; p++) {
                output(*p, context);
            }
        }
        *format += 2;
        return 1;
    }
    else if (strncmp(fmt, "%mf", 3) == 0) {
        float value = (float)va_arg(*args, double); 
        char buffer[256];
        
        if (memory_dump_float(value, buffer, sizeof(buffer)) == STATUS_OK) {
            for (const char* p = buffer; *p; p++) {
                output(*p, context);
            }
        }
        *format += 2;
        return 1;
    }
    else if (strncmp(fmt, "%md", 3) == 0) {
        double value = va_arg(*args, double);
        char buffer[512];
        
        if (memory_dump_double(value, buffer, sizeof(buffer)) == STATUS_OK) {
            for (const char* p = buffer; *p; p++) {
                output(*p, context);
            }
        }
        *format += 2;
        return 1;
    }
    
    return 0;
}

int overprintf_core(void (*output_func)(char, void*), void* context, 
                   const char* format, va_list args) {
    int count = 0;
    OutputContext* ctx = (OutputContext*)context;
    
    if (!output_func || !format || !context) {
        return -1;
    }
    
    while (*format) {
        if (*format == '%') {
            if (handle_special_format(output_func, context, &format, &args)) {
                count++;
                format++;
                continue;
            }
            
            format++;
            if (*format == 'd' || *format == 'i') {
                int value = va_arg(args, int);
                char buffer[20];
                snprintf(buffer, sizeof(buffer), "%d", value);
                for (const char* p = buffer; *p; p++) {
                    output_func(*p, context);
                    count++;
                }
            }
            else if (*format == 'u') {
                unsigned int value = va_arg(args, unsigned int);
                char buffer[20];
                snprintf(buffer, sizeof(buffer), "%u", value);
                for (const char* p = buffer; *p; p++) {
                    output_func(*p, context);
                    count++;
                }
            }
            else if (*format == 's') {
                char* str = va_arg(args, char*);
                for (const char* p = str; *p; p++) {
                    output_func(*p, context);
                    count++;
                }
            }
            else if (*format == 'c') {
                char c = (char)va_arg(args, int);
                output_func(c, context);
                count++;
            }
            else if (*format == '%') {
                output_func('%', context);
                count++;
            }
            else {
                output_func('%', context);
                output_func(*format, context);
                count += 2;
            }
        } else {
            output_func(*format, context);
            count++;
        }
        
        format++;
    }
    
    if (ctx->buffer && ctx->pos < ctx->size) {
        ctx->buffer[ctx->pos] = '\0';
    }
    
    return count;
}

int overfprintf(FILE* stream, const char* format, ...) {
    if (!stream || !format) {
        return -1;
    }
    
    OutputContext context = {stream, NULL, 0, 0};
    va_list args;
    va_start(args, format);
    int result = overprintf_core(stream_output, &context, format, args);
    va_end(args);
    
    return result;
}

int oversprintf(char* str, const char* format, ...) {
    if (!str || !format) {
        return -1;
    }
    
    OutputContext context = {NULL, str, MAX_BUFFER_SIZE, 0};
    va_list args;
    va_start(args, format);
    int result = overprintf_core(buffer_output, &context, format, args);
    va_end(args);
    
    return result;
}