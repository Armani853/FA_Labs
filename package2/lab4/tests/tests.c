#include <assert.h>
#include <stdio.h>
#include "../include/functions.h"

void test_roman_to_int() {
    printf("Testing roman_to_int...\n");
    
    int result;
    
    assert(roman_to_int("I", &result) == STATUS_OK && result == 1);
    assert(roman_to_int("V", &result) == STATUS_OK && result == 5);
    assert(roman_to_int("X", &result) == STATUS_OK && result == 10);
    
    assert(roman_to_int("IV", &result) == STATUS_OK && result == 4);
    assert(roman_to_int("IX", &result) == STATUS_OK && result == 9);
    assert(roman_to_int("XIV", &result) == STATUS_OK && result == 14);
    
    assert(roman_to_int("MMXXIII", &result) == STATUS_OK && result == 2023);
    
    printf("All roman_to_int tests passed!\n");
}

void test_zeckendorf_to_uint() {
    printf("Testing zeckendorf_to_uint...\n");
    
    unsigned int result;
    
    assert(zeckendorf_to_uint("11", &result) == STATUS_OK && result == 1);
    assert(zeckendorf_to_uint("011", &result) == STATUS_OK && result == 2);
    assert(zeckendorf_to_uint("1011", &result) == STATUS_OK && result == 4);

    printf("All zeckendorf_to_uint tests passed!\n");
}

void test_scan_custom_base() {
    printf("Testing scan_custom_base...\n");
    
    int result;
    const char *str;
    
    str = "1010";
    assert(scan_custom_base(&str, &result, 2, 0) == STATUS_OK && result == 10);
    
    str = "42";
    assert(scan_custom_base(&str, &result, 10, 0) == STATUS_OK && result == 42);
    
    str = "ff";
    assert(scan_custom_base(&str, &result, 16, 0) == STATUS_OK && result == 255);
    
    str = "1A";
    assert(scan_custom_base(&str, &result, 16, 1) == STATUS_OK && result == 26);
    
    printf("All scan_custom_base tests passed!\n");
}

void test_oversscanf() {
    printf("Testing oversscanf...\n");
    
    int num1, num2, num3;
    unsigned int unum1, unum2;
    
    const char *str1 = "XIV 42";
    assert(oversscanf(str1, "%Ro %d", &num1, &num2) == 2);
    assert(num1 == 14 && num2 == 42);
    
    const char *str2 = "11 011";
    assert(oversscanf(str2, "%Zr %Zr", &unum1, &unum2) == 2);
    assert(unum1 == 1 && unum2 == 2);
    
    const char *str3 = "1010 ff";
    assert(oversscanf(str3, "%Cv %Cv", &num1, 2, &num2, 16) == 2);
    assert(num1 == 10 && num2 == 255);
    
    const char *str4 = "X 1010 10";
    assert(oversscanf(str4, "%Ro %Cv %d", &num1, &num2, 2, &num3) == 3);
    assert(num1 == 10 && num2 == 10 && num3 == 10);
    
    printf("All oversscanf tests passed!\n");
}

void test_overfscanf() {
    printf("Testing overfscanf...\n");
    
    FILE *test_file = fopen("test_4lab.txt", "w+");
    if (!test_file) {
        printf("Cannot create test file, skipping overfscanf tests\n");
        return;
    }
    
    fprintf(test_file, "XIV 11 1010 42");
    rewind(test_file);
    
    int roman_num, binary_num, decimal_num;
    unsigned int zeck_num;
    
    int count = overfscanf(test_file, "%Ro %Zr %Cv %d", &roman_num, &zeck_num, &binary_num, 2, &decimal_num);
    
    assert(count == 4);
    assert(roman_num == 14);
    assert(zeck_num == 1);
    assert(binary_num == 10);
    assert(decimal_num == 42);
    
    fclose(test_file);
    remove("test_input.txt");
    
    printf("All overfscanf tests passed!\n");
}

int main() {
    printf("Running all tests...\n\n");
    
    test_roman_to_int();
    test_zeckendorf_to_uint();
    test_scan_custom_base();
    test_oversscanf();
    test_overfscanf();
    
    printf("\n All tests passed successfully!\n");
    return 0;
}