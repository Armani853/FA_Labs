#include <stdio.h>
#include "../include/functions.h"
int main() {
    printf("Testing overfprintf and oversprintf:\n\n");
    
    printf("1. Roman numerals (%%Ro):\n");
    overfprintf(stdout, "15 in Roman: %Ro\n", 15);
    overfprintf(stdout, "2023 in Roman: %Ro\n", 2023);
    
    printf("\n2. Zeckendorf representation (%%Zr):\n");
    overfprintf(stdout, "20 in Zeckendorf: %Zr\n", 20U);
    
    printf("\n3. Custom base (%%Cv, %%CV):\n");
    overfprintf(stdout, "255 in hex (lower): %Cv\n", 255, 16);
    overfprintf(stdout, "255 in hex (upper): %CV\n", 255, 16);
    
    printf("\n4. Base conversion (%%to, %%TO):\n");
    overfprintf(stdout, "FF from hex: %to\n", "ff", 16);
    
    printf("\n5. Memory dump:\n");
    int test_int = 123456;
    overfprintf(stdout, "Int %d memory: %mi\n", test_int, test_int);
    
    
    printf("\n6. Testing oversprintf:\n");
    char buffer[256];
    oversprintf(buffer, "Roman: %Ro, Zeck: %Zr", 42, 42U);
    printf("Result: %s\n", buffer);
    
    return 0;
}