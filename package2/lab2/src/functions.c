#include "../include/functions.h"
#include <stdio.h>


const char *const LINUX_ERRORS[] = {
    "Success",                  
    "Operation not permitted",  
    "No such file or directory",
    "No such process",          
    "Interrupted system call",  
    "I/O error",                
    "No such device or address"
};

const char *const MACOS_ERRORS[] = {
    "Success",                  
    "Operation not permitted", 
    "No such file or directory",
    "No such process",          
    "Interrupted system call",  
    "I/O error"               
};

StatusCode my_memchr(const void* str, int c, int n, void** ptr) {
    if (str == NULL || ptr == NULL) {
        return NULL_ERROR;
    }
    const unsigned char* p = (const unsigned char*)str;
    const unsigned uc = (unsigned char)c;
    if (n <= 0) {
        return OUT_OF_RANGE_ERROR;
    }

    for (int i = 0; i < n; i++) {
        if (uc == p[i]) {
            *ptr = (void*)(p + i);
            return STATUS_OK;
        }
    }
    *ptr = NULL;
    return NOT_FOUND_ERROR;
}

StatusCode my_memcmp(const void* str1, const void* str2, int n, int* res) {
    if (str1 == NULL || str2 == NULL || res == NULL) {
        return NULL_ERROR;
    }
    const char* p1 = (const char*)str1;
    const char* p2 = (const char*)str2;
    for (int i = 0;  i < n; i++) {
        if (p1[i] != p2[i]) {
            *res = (int)p1[i] - (int)p2[i];
            return STATUS_OK;
        }
    }
    *res = 0;
    return STATUS_OK;
}

StatusCode my_memcpy(void* dest, const void* src, int n, void** res) {
    if (dest == NULL || src == NULL || res == NULL) {
        return NULL_ERROR;
    }
    unsigned char* d = (unsigned char*)dest;
    unsigned char* s = (unsigned char*)src;
    for (int i = 0; i < n; i++) {
        d[i] = s[i];
    }
    *res = dest; 
    return STATUS_OK;
}

StatusCode my_memset(void *str, int c, int n, void **res) {
    if (str == NULL || res == NULL) {
        return NULL_ERROR;
    } 

    unsigned char *p = (unsigned char*)str;
    unsigned char uc = (unsigned char)c;

    for (int i = 0; i < n; ++i) {
        p[i] = uc;
    }

    *res = str;
    return STATUS_OK;
}

StatusCode my_strncat(char *dest, const char *src, int n, char **res) {
    if (dest == NULL || src == NULL || res == NULL) {
        return NULL_ERROR;
    } 

    char *d = dest;
    int src_len = 0;

    while (*d != '\0') {
        d++;
    }

    for (int i = 0; i < n && src[i] != '\0'; ++i) {
        *d = src[i];
        src_len++;
        d++;
    }

    *d = '\0';
    
    *res = dest;
    return STATUS_OK;
}


StatusCode my_strchr(const char *str, int c, char **res) {
    if (str == NULL || res == NULL) {
        return NULL_ERROR;
    }

    char *p = (char *)str;
    unsigned char uc = (unsigned char)c;

    do {
        if (*p == uc) {
            *res = p;
            return STATUS_OK;
        }
    } while (*p++ != '\0');

    *res = NULL;
    return NOT_FOUND_ERROR;
}

StatusCode my_strncmp(const char *str1, const char *str2, int n, int *res) {
    if (str1 == NULL || str2 == NULL || res == NULL) {
        return NULL_ERROR;
    }

    const unsigned char *p1 = (const unsigned char *)str1;
    const unsigned char *p2 = (const unsigned char *)str2;

    for (int i = 0; i < n; ++i) {
        if (p1[i] != p2[i] || p1[i] == '\0') {
            *res = (int)p1[i] - (int)p2[i];
            return STATUS_OK;
        }
    }

    *res = 0;
    return STATUS_OK;
}

StatusCode my_strncpy(char *dest, const char *src, int n, char **res) {
    if (dest == NULL || src == NULL || res == NULL) {
        return NULL_ERROR;
    }
    if (n == 0) {
        *res = dest;
        return STATUS_OK; 
    } 

    char *d = dest;
    const char *s = src;
    int i = 0;

    for (; i < n && *s != '\0'; ++i) {
        *d++ = *s++;
    }

    for (; i < n; ++i) {
        *d++ = '\0';
    }

    *res = dest;
    return STATUS_OK;
}

StatusCode my_strcspn(const char *str1, const char *str2, int* result) {
    if (str1 == NULL || str2 == NULL || result == NULL) {
        return NULL_ERROR;
    }

    const char *p1 = str1;
    const char *p2;

    while (*p1 != '\0') {
        p2 = str2;
        while (*p2 != '\0') {
            if (*p1 == *p2) {
                *result = (int)(p1 - str1);
                return STATUS_OK;
            }
            p2++;
        }
        p1++;
    }

    *result = (int)(p1 - str1); 
    return STATUS_OK;
}

char *my_strerror(int errnum) {
    #ifdef __linux__
        if (errnum >= 0 && errnum < LINUX_ERRORS_COUNT) {
            return (char *)LINUX_ERRORS[errnum];
        }
    #elif defined(__APPLE__)
        if (errnum >= 0 && errnum < MACOS_ERRORS_COUNT) {
            return (char *)MACOS_ERRORS[errnum];
        }
    #endif

    return "Unknown error"; 
}

StatusCode my_strlen(const char *str, int* res) {
    if (str == NULL || res == NULL) {
        return NULL_ERROR;
    } 

    const char *p = str;
    while (*p != '\0') {
        p++;
    }

    *res = (int)(p - str);
    return STATUS_OK;
}

StatusCode my_strpbrk(const char *str1, const char *str2, char** res) {
    if (str1 == NULL || str2 == NULL || res == NULL) {
        return NULL_ERROR;
    }

    const char *p2;

    while (*str1 != '\0') {
        p2 = str2;
        while (*p2 != '\0') {
            if (*str1 == *p2) {
                *res = (char *)str1;
                return STATUS_OK;
            }
            p2++;
        }
        str1++;
    }

    *res = NULL;
    return NOT_FOUND_ERROR;
}

StatusCode my_strrchr(const char *str, int c, char** res) {
    if (str == NULL || res == NULL) {
        return NULL_ERROR;
    }

    char *last = NULL;
    char *p = (char *)str;
    unsigned char uc = (unsigned char)c;

    do {
        if (*p == uc) {
            last = p;
        }
    } while (*p++ != '\0');

    *res = last;
    if (last == NULL) {
        return NOT_FOUND_ERROR;
    }
    return STATUS_OK;
}

StatusCode my_strstr(const char *haystack, const char *needle, char** res) {
    if (haystack == NULL || needle == NULL || res == NULL) {
        return NULL_ERROR;
    }

    if (*needle == '\0') {
        *res = (char *)haystack;
        return STATUS_OK;
    }

    const char *h_ptr;
    const char *n_ptr;

    while (*haystack != '\0') {
        h_ptr = haystack;
        n_ptr = needle;

        while (*n_ptr != '\0' && *h_ptr == *n_ptr) {
            h_ptr++;
            n_ptr++;
        }

        if (*n_ptr == '\0') {
            *res = (char *)haystack;
            return STATUS_OK;
        }

        haystack++;
    }

    *res = NULL;
    return NOT_FOUND_ERROR;
}

char* my_strtok(char *str, const char *delim) {
    static char *last = NULL;
    
    if (str != NULL) {
        last = str;
    }
    
    last += strspn(last, delim);
    
    if (*last == '\0') {
        last = NULL;
        return NULL;
    }
    
    char *token = last;
    
    last = strpbrk(token, delim);
    
    if (last == NULL) {
    } else {
        *last = '\0';
        last++;
    }

    return token;
}

void print_status(StatusCode s) {
    switch (s) {
        case STATUS_OK:
            printf("Успешно\n");
            break;
        case NULL_ERROR:
            printf("Нулевой указатель\n");
            break;
        case NOT_FOUND_ERROR:
            printf("Не найдено\n");
            break;
        case OUT_OF_RANGE_ERROR:
            printf("Выход за пределы цикла\n");
            break;
        case INVALID_ERRNUM:
            printf("Неверный номер ошибки\n");
            break;
        default:
            printf("Неизвестная ошибка\n");
            break;
    }
}

