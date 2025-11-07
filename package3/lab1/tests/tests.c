#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/functions.h" 

#define TEST_PASS (printf("TEST PASSED: %s\n", __func__))

void test_octal_conversion() {
    char buf[BUF_SIZE];
    StatusCode st = convert_to_r_base(175, 3, buf);
    
    assert(st == STATUS_OK); 
    
    assert(strcmp(buf, "257") == 0);
    
    TEST_PASS;
}

void test_base32_conversion() {
    char buf[BUF_SIZE];
    StatusCode st = convert_to_r_base(31, 5, buf);
    
    assert(st == STATUS_OK);
    assert(strcmp(buf, "V") == 0); 
    
    TEST_PASS;
}

void test_zero_conversion() {
    char buf[BUF_SIZE];
    StatusCode st = convert_to_r_base(0, 4, buf);
    
    assert(st == STATUS_OK);
    assert(strcmp(buf, "0") == 0);
    
    TEST_PASS;
}

void test_invalid_input_r() {
    char buf[BUF_SIZE];
    StatusCode st = convert_to_r_base(100, 6, buf);
    
    assert(st == INVALID_INPUT); 
    
    TEST_PASS;
}


int main() {
    printf("--- Running Unit Tests ---\n");
    test_octal_conversion();
    test_base32_conversion();
    test_zero_conversion();
    test_invalid_input_r();
    printf("ALL ASSERTS PASSED!\n");
    return 0;
}