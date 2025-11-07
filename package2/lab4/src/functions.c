#include "../include/functions.h"

int is_roman_char(char c) {
    c = toupper(c);
    return (c == 'I' || c == 'V' || c == 'X' || c == 'L' || 
            c == 'C' || c == 'D' || c == 'M');
}

int roman_to_int(const char *str, int *result) {
    if (!str || !result) return INVALID_INPUT;
    
    int values[256] = {0};
    values['I'] = values['i'] = 1;
    values['V'] = values['v'] = 5;
    values['X'] = values['x'] = 10;
    values['L'] = values['l'] = 50;
    values['C'] = values['c'] = 100;
    values['D'] = values['d'] = 500;
    values['M'] = values['m'] = 1000;
    
    int total = 0;
    int prev_value = 0;
    int length = 0;
    
    for (const char *p = str; *p; p++) {
        if (!is_roman_char(*p)) {
            return INVALID_INPUT;
        }
        length++;
        if (length > 15) return INVALID_INPUT;
    }
    
    for (int i = length - 1; i >= 0; i--) {
        int current = values[(unsigned char)str[i]];
        
        if (current < prev_value) {
            total -= current;
        } else {
            total += current;
        }
        prev_value = current;
    }
    
    if (total < 1 || total > 3999) {
        return INVALID_INPUT;
    }
    
    *result = total;
    return STATUS_OK;
}

int generate_fibonacci(unsigned int n, unsigned int **fib_sequence, int *size) {
    if (n == 0) {
        *size = 0;
        *fib_sequence = NULL;
        return STATUS_OK;
    }
    
    int max_size = 50;
    unsigned int *fib = (unsigned int*)malloc(max_size * sizeof(unsigned int));
    if (!fib) return MEMORY_ERROR;
    
    fib[0] = 1;
    fib[1] = 2;
    int count = 2;
    
    while (count < max_size) {
        fib[count] = fib[count-1] + fib[count-2];
        if (fib[count] > n) break;
        count++;
    }
    
    *fib_sequence = fib;
    *size = count;
    return STATUS_OK;
}

int zeckendorf_to_uint(const char *str, unsigned int *result) {
    if (!str || !result) return INVALID_INPUT;
    
    int len = strlen(str);
    if (len < 2) return INVALID_INPUT;
    
    if (str[len-1] != '1') return INVALID_INPUT;
    
    for (int i = 0; i < len - 1; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return INVALID_INPUT;
        }
    }
    
    for (int i = 0; i < len - 2; i++) {
        if (str[i] == '1' && str[i+1] == '1') {
            return INVALID_INPUT;
        }
    }
    
    unsigned int max_possible = MAX_FIB;
    unsigned int *fib;
    int fib_size;
    int status = generate_fibonacci(max_possible, &fib, &fib_size);
    if (status != STATUS_OK) return status;
    
    unsigned int value = 0;
    int bit_index = 0;
    
    for (int i = 0; i < len - 1; i++) {
        if (str[i] == '1') {
            if (bit_index < fib_size) {
                value += fib[bit_index];
            }
        }
        bit_index++;
    }
    
    free(fib);
    *result = value;
    return STATUS_OK;
}

int skip_whitespace_stream(FILE *stream) {
    if (!stream) return INVALID_INPUT;
    
    int c;
    while ((c = fgetc(stream)) != EOF && isspace(c)) {
    }
    if (c != EOF) ungetc(c, stream);
    return STATUS_OK;
}

int skip_whitespace_string(const char **str) {
    if (!str || !*str) return INVALID_INPUT;
    
    while (**str && isspace((unsigned char)**str)) {
        (*str)++;
    }
    return STATUS_OK;
}

int scan_custom_base(const char **str, int *result, int base, int uppercase) {
    if (!str || !*str || !result) return INVALID_INPUT;
    
    if (base < 2 || base > 36) {
        base = 10;
    }
    
    const char *ptr = *str;
    long long value = 0;
    int sign = 1;
    int digits_found = 0;
    
    while (*ptr && isspace((unsigned char)*ptr)) {
        ptr++;
    }
    
    if (*ptr == '-') {
        sign = -1;
        ptr++;
    } else if (*ptr == '+') {
        ptr++;
    }
    
    while (*ptr) {
        int digit = -1;
        char c = *ptr;
        
        if (isdigit((unsigned char)c)) {
            digit = c - '0';
        } else if (isalpha((unsigned char)c)) {
            if (uppercase) {
                c = toupper(c);
                digit = c - 'A' + 10;
            } else {
                c = tolower(c);
                digit = c - 'a' + 10;
            }
        }
        
        if (digit < 0 || digit >= base) {
            break;
        }
        

        if (value > (LLONG_MAX - digit) / base) {
            return INVALID_INPUT;
        }
        
        value = value * base + digit;
        digits_found = 1;
        ptr++;
    }
    
    if (!digits_found) {
        return NO_MATCH;
    }
    
    *result = (int)(value * sign);
    *str = ptr;
    return STATUS_OK;
}


int process_specifier(const char **format, va_list *args, 
                            FILE *stream, const char **str_input, int *success_count) {
    const char *fmt_ptr = *format;
    
    while (*fmt_ptr && isspace((unsigned char)*fmt_ptr)) {
        fmt_ptr++;
    }
    
    if (*fmt_ptr == '\0') {
        return OVERSCANF_EOF;
    }
    
    if (*fmt_ptr != '%') {
        if (stream) {
            int c = fgetc(stream);
            if (c == EOF) return OVERSCANF_EOF;
            if (c != *fmt_ptr) {
                ungetc(c, stream);
                return NO_MATCH;
            }
        } else {
            skip_whitespace_string(str_input);
            if (**str_input != *fmt_ptr) {
                return NO_MATCH;
            }
            (*str_input)++;
        }
        (*format)++;
        return STATUS_OK;
    }
    
    fmt_ptr++;
    
    if (stream) {
        skip_whitespace_stream(stream);
    } else {
        skip_whitespace_string(str_input);
    }
    
    if (strncmp(fmt_ptr, "Ro", 2) == 0) {
        fmt_ptr += 2;
        int *target = va_arg(*args, int*);
        
        char buffer[32] = {0};
        int buf_index = 0;
        
        if (stream) {
            int c;
            while ((c = fgetc(stream)) != EOF && !isspace(c) && buf_index < 31) {
                if (!is_roman_char(c)) {
                    ungetc(c, stream);
                    break;
                }
                buffer[buf_index++] = c;
            }
        } else {
            while (**str_input && !isspace(**str_input) && buf_index < 31) {
                if (!is_roman_char(**str_input)) break;
                buffer[buf_index++] = *(*str_input)++;
            }
        }
        
        if (buf_index == 0) return NO_MATCH;
        
        int status = roman_to_int(buffer, target);
        if (status == STATUS_OK) {
            (*success_count)++;
        }
        *format = fmt_ptr;
        return status;
    }
    else if (strncmp(fmt_ptr, "Zr", 2) == 0) {
        fmt_ptr += 2;
        unsigned int *target = va_arg(*args, unsigned int*);
        
        char buffer[64] = {0};
        int buf_index = 0;
        
        if (stream) {
            int c;
            while ((c = fgetc(stream)) != EOF && !isspace(c) && buf_index < 63) {
                if (c != '0' && c != '1') {
                    ungetc(c, stream);
                    break;
                }
                buffer[buf_index++] = c;
            }
        } else {
            while (**str_input && !isspace(**str_input) && buf_index < 63) {
                char c = **str_input;
                if (c != '0' && c != '1') break;
                buffer[buf_index++] = *(*str_input)++;
            }
        }
        
        if (buf_index == 0) return NO_MATCH;
        
        int status = zeckendorf_to_uint(buffer, target);
        if (status == STATUS_OK) {
            (*success_count)++;
        }
        *format = fmt_ptr;
        return status;
    }
    else if (strncmp(fmt_ptr, "Cv", 2) == 0 || strncmp(fmt_ptr, "CV", 2) == 0) {
        int uppercase = (fmt_ptr[1] == 'V');
        fmt_ptr += 2;
        
        int *target = va_arg(*args, int*);
        int base = va_arg(*args, int);
        
        if (stream) {
            char buffer[64] = {0};
            int buf_index = 0;
            int c;
            
            while ((c = fgetc(stream)) != EOF && !isspace(c) && buf_index < 63) {
                buffer[buf_index++] = c;
            }
            
            if (buf_index == 0) return NO_MATCH;
            
            const char *buf_ptr = buffer;
            int status = scan_custom_base(&buf_ptr, target, base, uppercase);
            if (status == STATUS_OK) {
                (*success_count)++;
            }
            *format = fmt_ptr;
            return status;
        } else {
            const char *save_ptr = *str_input;
            int status = scan_custom_base(str_input, target, base, uppercase);
            if (status == STATUS_OK) {
                (*success_count)++;
            } else {
                *str_input = save_ptr;
            }
            *format = fmt_ptr;
            return status;
        }
    }
    else if (*fmt_ptr == 'd') {
        fmt_ptr++;
        int *target = va_arg(*args, int*);
        
        if (stream) {
            if (fscanf(stream, "%d", target) == 1) {
                (*success_count)++;
                *format = fmt_ptr;
                return STATUS_OK;
            } else {
                return NO_MATCH;
            }
        } else {
            char *end;
            long value = strtol(*str_input, &end, 10);
            if (end != *str_input) {
                *target = (int)value;
                *str_input = end;
                (*success_count)++;
                *format = fmt_ptr;
                return STATUS_OK;
            } else {
                return NO_MATCH;
            }
        }
    }
    else if (*fmt_ptr == 'u') {
        fmt_ptr++;
        unsigned int *target = va_arg(*args, unsigned int*);
        
        if (stream) {
            if (fscanf(stream, "%u", target) == 1) {
                (*success_count)++;
                *format = fmt_ptr;
                return STATUS_OK;
            } else {
                return NO_MATCH;
            }
        } else {
            char *end;
            unsigned long value = strtoul(*str_input, &end, 10);
            if (end != *str_input) {
                *target = (unsigned int)value;
                *str_input = end;
                (*success_count)++;
                *format = fmt_ptr;
                return STATUS_OK;
            } else {
                return NO_MATCH;
            }
        }
    }
    else {
        return INVALID_INPUT;
    }
}

int overfscanf(FILE *stream, const char *format, ...) {
    if (!stream || !format) return -1;
    
    va_list args;
    va_start(args, format);
    
    int success_count = 0;
    const char *fmt_ptr = format;
    
    while (*fmt_ptr) {
        int status = process_specifier(&fmt_ptr, &args, stream, NULL, &success_count);
        if (status == OVERSCANF_EOF || status == NO_MATCH) {
            break;
        }
    }
    
    va_end(args);
    return success_count;
}

int oversscanf(const char *str, const char *format, ...) {
    if (!str || !format) return -1;
    
    va_list args;
    va_start(args, format);
    
    int success_count = 0;
    const char *fmt_ptr = format;
    const char *str_ptr = str;
    
    while (*fmt_ptr && *str_ptr) {
        int status = process_specifier(&fmt_ptr, &args, NULL, &str_ptr, &success_count);
        if (status == NO_MATCH) {
            break;
        }
    }
    
    va_end(args);
    return success_count;
}