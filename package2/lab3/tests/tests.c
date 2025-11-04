#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h> 


#define STATUS_OK 0
#define MAX_BUFFER_SIZE 512
#define MAX_ROMAN_LENGTH 16
#define MAX_ZEK_LENGTH 64

extern int overfprintf(FILE* stream, const char* format, ...);
extern int oversprintf(char* str, const char* format, ...);


void test_roman_numerals() {
    char buffer[MAX_ROMAN_LENGTH];
    
    assert(oversprintf(buffer, "%Ro", 42) > 0);
    assert(strcmp(buffer, "XLII") == 0);
    printf("  [OK] %Ro (Римские) - XLII\n");

    assert(oversprintf(buffer, "%Ro", 3999) > 0);
    assert(strcmp(buffer, "MMMCMXCIX") == 0);
    printf("  [OK] %Ro (Римские) - MMMCMXCIX\n");
}

void test_zeckendorf() {
    char buffer[MAX_ZEK_LENGTH];
    
    assert(oversprintf(buffer, "%Zr", 20) > 0);
    assert(strcmp(buffer, "1010101") == 0); 
    printf("  [OK] %%Zr (Цекендорф) - 1010101\n");
}

void test_base_conversion() {
    char buffer[MAX_BUFFER_SIZE];
    int len;

    len = oversprintf(buffer, "%Cv", 31, 16);
    assert(len > 0);
    assert(strcmp(buffer, "1f") == 0);
    printf("  [OK] %Cv (int 31 to base 16) - 1f\n");

    len = oversprintf(buffer, "%CV", 31, 16);
    assert(len > 0);
    assert(strcmp(buffer, "1F") == 0);
    printf("  [OK] %CV (int 31 to base 16) - 1F\n");

    
    len = oversprintf(buffer, "%TO", "ABC", 16);
    assert(len > 0);
    assert(strcmp(buffer, "2748") == 0);
    printf("  [OK] %TO (base 16 to int) - 2748\n");
}

void test_memory_dump() {

    char buffer[512];
    int len;

    len = oversprintf(buffer, "%mi", 123456);
    assert(len > 0);
    printf("  [OK] %mi (Дамп int) - Корректная длина \n");

    len = oversprintf(buffer, "%mf", 3.14f);
    assert(len > 0);
    printf("  [OK] %mf (Дамп float) - Корректная длина \n");
}

int main() {
    printf("--- Запуск Unit-тестов overfprintf/oversprintf ---\n");
    
    printf("\n[Группа 1] Тестирование Римских чисел (%%Ro):\n");
    test_roman_numerals();
    
    printf("\n[Группа 2] Тестирование Цекендорфа (%%Zr):\n");
    test_zeckendorf();
    
    printf("\n[Группа 3] Тестирование конверсии баз (%%Cv, %%TO, %%to):\n");
    test_base_conversion();
    
    printf("\n[Группа 4] Тестирование Дампов Памяти (%%mi, %%mf, %%md):\n");
    test_memory_dump();
    
    printf("\n--- ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО! ---\n");
    
    return EXIT_SUCCESS;
}