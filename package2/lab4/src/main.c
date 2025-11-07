#include "../include/functions.h"

void demo_oversscanf() {
    printf("=== ДЕМОНСТРАЦИЯ oversscanf ===\n\n");
    
    printf("1. Римские цифры (%%Ro):\n");
    const char *test1 = "XIV 42 MMXXIII";
    int roman1 = 0, num1 = 0, roman2 = 0;
    
    int count = oversscanf(test1, "%Ro %d %Ro", &roman1, &num1, &roman2);
    printf("   Вход: \"%s\"\n", test1);
    printf("   Формат: %%Ro %%d %%Ro\n");
    printf("   Результат: count=%d, XIV=%d, 42=%d, MMXXIII=%d\n\n", count, roman1, num1, roman2);
    
    printf("2. Представление Цекендорфа (%%Zr):\n");
    const char *test2 = "11 011 1011";
    unsigned int z1 = 0, z2 = 0, z3 = 0;
    
    count = oversscanf(test2, "%Zr %Zr %Zr", &z1, &z2, &z3);
    printf("   Вход: \"%s\"\n", test2);
    printf("   Формат: %%Zr %%Zr %%Zr\n");
    printf("   Результат: count=%d, 11=%u, 011=%u, 1011=%u\n\n", count, z1, z2, z3);
    
    printf("3. Кастомные системы счисления (%%Cv, %%CV):\n");
    const char *test3 = "1010 ff 1A";
    int bin = 0, hex_lower = 0, hex_upper = 0;
    
    count = oversscanf(test3, "%Cv %Cv %CV", &bin, 2, &hex_lower, 16, &hex_upper, 16);
    printf("   Вход: \"%s\"\n", test3);
    printf("   Формат: %%Cv(2) %%Cv(16) %%CV(16)\n");
    printf("   Результат: count=%d, 1010(bin)=%d, ff(hex)=%d, 1A(hex)=%d\n\n", count, bin, hex_lower, hex_upper);
    
    printf("4. Смешанные форматы:\n");
    const char *test4 = "X 1010 1a 255";
    int roman = 0, binary = 0, hex = 0, decimal = 0;
    
    count = oversscanf(test4, "%Ro %Cv %Cv %d", &roman, &binary, 2, &hex, 16, &decimal);
    printf("   Вход: \"%s\"\n", test4);
    printf("   Формат: %%Ro %%Cv(2) %%Cv(16) %%d\n");
    printf("   Результат: count=%d, X=%d, 1010(bin)=%d, 1a(hex)=%d, 255=%d\n\n", count, roman, binary, hex, decimal);
}

void demo_overfscanf() {
    printf("=== ДЕМОНСТРАЦИЯ overfscanf (через консоль) ===\n\n");
    
    printf("Введите данные в формате: [римское] [цекендорф] [двоичное] [десятичное]\n");
    printf("Пример: XIV 1011 1101 42\n");
    printf("Ваш ввод: ");
    fflush(stdout);
    
    int roman_num = 0, binary_num = 0, decimal_num = 0;
    unsigned int zeck_num = 0;
    
    int count = overfscanf(stdin, "%Ro %Zr %Cv %d", &roman_num, &zeck_num, &binary_num, 2, &decimal_num);
    
    printf("\nРезультат:\n");
    printf("Считано значений: %d\n", count);
    if (count >= 1) printf("Римское: %d\n", roman_num);
    if (count >= 2) printf("Цекендорф: %u\n", zeck_num);
    if (count >= 3) printf("Двоичное: %d\n", binary_num);
    if (count >= 4) printf("Десятичное: %d\n", decimal_num);
}

void test_functions() {
    printf("\n=== ТЕСТИРОВАНИЕ ВСПОМОГАТЕЛЬНЫХ ФУНКЦИЙ ===\n\n");
    
    printf("Тест римских цифр:\n");
    int result;
    int status = roman_to_int("XIV", &result);
    printf("   XIV -> %d (статус: %d)\n", result, status);
    
    status = roman_to_int("XLII", &result);
    printf("   XLII -> %d (статус: %d)\n", result, status);
    
    printf("\nТест Цекендорфа:\n");
    unsigned int zresult;
    status = zeckendorf_to_uint("1011", &zresult);
    printf("   1011 -> %u (статус: %d)\n", zresult, status);
    
    status = zeckendorf_to_uint("011", &zresult);
    printf("   011 -> %u (статус: %d)\n", zresult, status);
    
    printf("\nТест кастомных систем:\n");
    const char *num_str = "1a";
    const char *ptr = num_str;
    status = scan_custom_base(&ptr, &result, 16, 0);
    printf("   1a(hex) -> %d (статус: %d), остаток: '%s'\n", result, status, ptr);
}

int main() {
    printf("ДЕМОНСТРАЦИЯ РАБОТЫ overfscanf/oversscanf\n");
    printf("==========================================\n\n");
    
    demo_oversscanf();
    test_functions();
    demo_overfscanf();
    
    printf("\nНажмите Enter для выхода...");
    getchar();
    
    return 0;
}