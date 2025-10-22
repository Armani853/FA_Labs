#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/functions.h"

void test_mem_func() {
    StatusCode s;
    char dest[ARRAY_SIZE] = "Hello, World!";
    char dop[ARRAY_SIZE] = "Hello, Earth!";
    char buff[ARRAY_SIZE];
    void* ptr_res;
    int int_res;

    printf("Тестирование функций для работы с памятью\n");
    printf("Функция memchr: ");
    s = my_memchr(&dest[0], 'W', sizeof(dest), &ptr_res);
    print_status(s);
    if (s == STATUS_OK) {
        printf("Результат найден по индексу %ld\n", (char*)ptr_res - dest);
    }

    printf("Функция memcmp: ");
    s = my_memcmp(&dest[0], &dop[0], sizeof(dest), &int_res);
    print_status(s);
    if (s == STATUS_OK) {
        printf("Результат: %d\n", int_res);
    }
    
    printf("Функция memcpy: ");
    s = my_memcpy(&buff[0], &dest[0], sizeof(dest), &ptr_res);
    print_status(s);
    if (s == STATUS_OK) {
        printf("Результат: %s\n", (char*)ptr_res);
    }
    
    printf("Функция memset: ");
    print_status(s);
    s = my_memset(&dest[0], 'A', 5, &ptr_res);
    if (s == STATUS_OK) {
        printf("Результат: %s\n", (char*)ptr_res);
    }
}

void test_str_func() {
    StatusCode s;
    char ft[ARRAY_SIZE] = "Hello ";
    char sd[ARRAY_SIZE] = "World and Peace";
    char new_str[ARRAY_SIZE];
    char* ex_ch;
    int int_res;
    printf("Тестирование функций для работы со строками\n");

    printf("Функция strncat: ");
    s = my_strncat(&ft[0], &sd[0], 5, &ex_ch);
    if (s == STATUS_OK) {
        printf("Результат: %s\n", ex_ch);
    }

    printf("Функция strchr: ");
    s = my_strchr(&ft[0], 'e', &ex_ch);
    if (s == STATUS_OK) {
        printf("Результат - буква e найдена по индексу: %ld\n", ex_ch - ft);
    }

    printf("Функция strncmp: ");
    s = my_strncmp(&ft[0], &sd[0], 3, &int_res);
    if (s == STATUS_OK) {
        printf("Результат: %d\n", int_res);
    }

    printf("Функция strncpy: ");
    s = my_strncpy(&new_str[0], &ft[0], 5, &ex_ch);
    if (s == STATUS_OK) {
        printf("Результат: %s\n", ex_ch);
    }

    printf("Функция strcspn: ");
    s = my_strcspn(&ft[0], "lo", &int_res);
    if (s == STATUS_OK) {
        printf("Результат %d\n", int_res);
    }

    printf("Функция strerror: ");
    printf("Ошибка 2: %s\n", my_strerror(2));
    printf("Ошибка 45: %s\n", my_strerror(45));

    printf("Функция strlen: ");
    s = my_strlen(&ft[0], &int_res);
    if (s == STATUS_OK) {
        printf("Результат: %d\n", int_res);
    }

    printf("Функция strpbrk: ");
    s = my_strpbrk(&ft[0], &sd[0], &ex_ch);
    if (s == STATUS_OK) {
        printf("Результат: %c\n", *ex_ch);
    }
    
    printf("Функция strrchr: ");
    s = my_strrchr(&ft[0], 'l', &ex_ch);
    if (s == STATUS_OK) {
        printf("Результат: %c\n", *ex_ch);
    }

    printf("Функция strstr: ");
    s = my_strstr(&ft[0], "ell", &ex_ch);
    if (s == STATUS_OK) {
        printf("Результат: %c\n", *ex_ch);
    }

    printf("Функция strtok: ");
    char s_tok[] = "a,b,c";
    char *token = my_strtok(s_tok, ",");
    printf(" Token 1: %s\n", token);
    token = my_strtok(NULL, ",");
    printf(" Token 2: %s\n", token);
}

int main() {
    test_mem_func();
    test_str_func();
}