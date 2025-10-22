#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#define ARRAY_SIZE 50

typedef enum {
    STATUS_OK = 0,
    NULL_ERROR = 1,
    NOT_FOUND_ERROR = 2,
    INVALID_ERRNUM = 3,
    OUT_OF_RANGE_ERROR = 4
} StatusCode;

// Объявления функций
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


void test_mem_func_assert() {
    StatusCode s;
    char dest[ARRAY_SIZE] = "Hello, World!";
    char dop[ARRAY_SIZE] = "Hello, Earth!";
    char buff[ARRAY_SIZE];
    void* ptr_res = NULL;
    int int_res = 0;

    s = my_memchr(&dest[0], 'W', sizeof(dest), &ptr_res);
    assert(s == STATUS_OK);
    assert(ptr_res == dest + 7);

    s = my_memchr(&dest[0], 'Z', sizeof(dest), &ptr_res);
    assert(s == NOT_FOUND_ERROR);
    assert(ptr_res == NULL);

    s = my_memcmp(&dest[0], &dop[0], 6, &int_res);
    assert(s == STATUS_OK);
    assert(int_res == 0);

    s = my_memcmp(&dest[0], &dop[0], sizeof(dest), &int_res);
    assert(s == STATUS_OK);
    assert(int_res == 'W' - 'E'); 

    s = my_memcpy(&buff[0], &dest[0], sizeof(dest), &ptr_res);
    assert(s == STATUS_OK);
    assert(memcmp(buff, dest, sizeof(dest)) == 0);

    s = my_memset(&dest[0], 'X', 5, &ptr_res);
    assert(s == STATUS_OK);
    assert(dest[0] == 'X' && dest[4] == 'X' && dest[5] == ',');
}

void test_str_func_assert() {
    StatusCode s;
    char ft[ARRAY_SIZE] = "Hello ";
    char sd[ARRAY_SIZE] = "World and Peace";
    char new_str[ARRAY_SIZE];
    char* ex_ch = NULL;
    int int_res = 0;

    s = my_strncat(&ft[0], &sd[0], 5, &ex_ch);
    assert(s == STATUS_OK);
    assert(strcmp(ft, "Hello World") == 0);

    s = my_strchr(&ft[0], 'l', &ex_ch);
    assert(s == STATUS_OK);
    assert(ex_ch == ft + 2);

    char s_tok[] = "a,b,c";
    char *token = my_strtok(s_tok, ",");
    assert(strcmp(token, "a") == 0);
    token = my_strtok(NULL, ",");
    assert(strcmp(token, "b") == 0);
    token = my_strtok(NULL, ",");
    assert(strcmp(token, "c") == 0);
}

void test_main() {
    printf("--- Запуск Assert-тестов для функций mem... ---\n");
    test_mem_func_assert();
    printf("Тесты mem... пройдены успешно.\n");

    printf("--- Запуск Assert-тестов для функций str... ---\n");
    test_str_func_assert();
    printf("Тесты str... пройдены успешно.\n");

    printf("ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!\n");
}

int main() {
    test_main();
    return 0;
}