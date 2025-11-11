#include <assert.h>
#include "../include/functions.h"

void run_bracket_tests() {
    printf(" НАЧАЛО ASSERT-ТЕСТИРОВАНИЯ \n");


    assert(check_brackets("") == BALANCED);
    printf("   [OK] Пустая строка\n");
    
    assert(check_brackets("abc 123 ,.< >") == BALANCED);
    printf("   [OK] Только игнорируемые символы\n");

    assert(check_brackets("(){}[]<>") == BALANCED);
    printf("   [OK] Простые пары всех типов\n");

    assert(check_brackets("([{}])") == BALANCED);
    assert(check_brackets("(({}))") == BALANCED);
    printf("   [OK] Правильная вложенность\n");
    
    assert(check_brackets("a (b {c [d <e>] f} g) h") == BALANCED);
    printf("   [OK] Сложный сбалансированный пример\n");
    
    assert(check_brackets("()[]{}<>") == BALANCED);
    printf("   [OK] Пустые скобки\n");

    printf("\n");
    
    assert(check_brackets("({[") == NOT_BALANCED);
    
    printf("   [OK] Лишняя открывающая\n");
    
    assert(check_brackets("}abc") == NOT_BALANCED);
    assert(check_brackets("([)])") == NOT_BALANCED);
    printf("   [OK] Лишняя закрывающая\n");

    assert(check_brackets("([)]") == NOT_BALANCED);
    assert(check_brackets("{<]>}") == NOT_BALANCED);
    printf("   [OK] Неправильный порядок закрытия\n");

    assert(check_brackets("{]") == NOT_BALANCED);
    assert(check_brackets("(<)>") == NOT_BALANCED);
    printf("   [OK] Несоответствие типов\n");

    printf("\n");
    printf(" ВСЕ %d ASSERT-ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!\n", 15); 
}

int main() {
    run_bracket_tests();
    return 0;
}