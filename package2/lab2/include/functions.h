#include "status_codes.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#define ARRAY_SIZE 50
#define LINUX_ERRORS_COUNT (sizeof(LINUX_ERRORS) / sizeof(LINUX_ERRORS[0]))
#define MACOS_ERRORS_COUNT (sizeof(MACOS_ERRORS) / sizeof(MACOS_ERRORS[0]))


StatusCode my_memchr(const void* str, int c, int n, void** ptr);

StatusCode my_memcmp(const void* str1, const void* str2, int n, int* res);

StatusCode my_memcpy(void* dest, const void* src, int n, void** res);

StatusCode my_memset(void *str, int c, int n, void **res);

StatusCode my_strncat(char *dest, const char *src, int n, char **res);

StatusCode my_strchr(const char *str, int c, char **res);

StatusCode my_strncmp(const char *str1, const char *str2, int n, int *res);

StatusCode my_strncpy(char *dest, const char *src, int n, char **res);

StatusCode my_strcspn(const char *str1, const char *str2, int* result);

char *my_strerror(int errnum);

StatusCode my_strlen(const char *str, int* res);

StatusCode my_strpbrk(const char *str1, const char *str2, char** res);

StatusCode my_strrchr(const char *str, int c, char** res);

StatusCode my_strstr(const char *haystack, const char *needle, char** res);

char* my_strtok(char *str, const char *delim);

void print_status(StatusCode s);
