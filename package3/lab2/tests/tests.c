#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h> 

#define VECTOR_TYPE char*
#include "../include/functions.h" 


VECTOR_TYPE str_copy_func(VECTOR_TYPE src) {
    if (src == NULL) return NULL;
    return strdup(src); 
}

void str_delete_func(VECTOR_TYPE src) {
    if (src != NULL) {
        free(src); 
    }
}


void assert_deep_copy(const char *s1, const char *s2) {
    assert(strcmp(s1, s2) == 0); 
    assert(s1 != s2); 
}


void test_create_and_push() {
    printf("Тест 1: Создание, push_back и рост...\n");
    Vector v = create_vector(2, str_copy_func, str_delete_func);
    
    assert(v.size == 0);
    assert(v.capacity == 2);
    assert(v.CopyFunc == str_copy_func);
    
    char *s1 = strdup("TestA"); 
    push_back_vector(&v, s1);
    
    assert_deep_copy(get_at_vector(&v, 0), "TestA");
    
    free(s1); 
    
    push_back_vector(&v, "TestB");
    push_back_vector(&v, "TestC");
    
    assert(v.size == 3);
    assert(v.capacity == 4);
    
    printf("   OK: Создание и рост работают.\n");
    erase_vector(&v);
}

void test_delete_and_get() {
    printf("Тест 2: Удаление по индексу и получение...\n");
    Vector v = create_vector(4, str_copy_func, str_delete_func);
    
    push_back_vector(&v, "First"); 
    push_back_vector(&v, "Middle");
    push_back_vector(&v, "Last"); 
    
    assert(v.size == 3);
    
    assert(strcmp(get_at_vector(&v, 1), "Middle") == 0);
    
    delete_at_vector(&v, 0); 
    
    assert(v.size == 2);
    
    assert(strcmp(get_at_vector(&v, 0), "Middle") == 0);
    assert(strcmp(get_at_vector(&v, 1), "Last") == 0);
    
    assert(get_at_vector(&v, 2) == VECTOR_ERROR_VALUE); 
    
    printf("   OK: Удаление и сдвиг работают.\n");
    erase_vector(&v);
}

void test_copy_and_equality() {
    printf("Тест 3: Копирование и сравнение...\n");
    Vector v1 = create_vector(4, str_copy_func, str_delete_func);
    push_back_vector(&v1, "Alpha");
    push_back_vector(&v1, "Beta");
    
    Vector *v2_ptr = copy_new_vector(&v1);
    Vector v2 = *v2_ptr;
    
    assert(is_equal_vector(&v1, &v2) == 1);
    

    assert_deep_copy(get_at_vector(&v1, 0), get_at_vector(&v2, 0)); 
    
    push_back_vector(&v1, "Gamma");
    assert(is_equal_vector(&v1, &v2) == 0);
    
    erase_vector(&v1);
    assert(v1.size == 0);
    
    delete_vector(&v1);
    free(v2_ptr); 

    printf("   OK: Копирование и сравнение работают.\n");
}

void test_error_handling() {
    printf("Тест 4: Обработка ошибок...\n");
    Vector v = create_vector(1, str_copy_func, str_delete_func);
    
    erase_vector(&v);
    assert(v.size == 0 && v.data == NULL);
    
    delete_at_vector(&v, 5);
    assert(v.size == 0);
    
    assert(get_at_vector(&v, 0) == VECTOR_ERROR_VALUE); 

    printf("   OK: Обработка ошибок завершена.\n");
}


int main() {

    printf("НАЧАЛО ТЕСТИРОВАНИЯ Vector \n");


    test_create_and_push();
    test_delete_and_get();
    test_copy_and_equality();
    test_error_handling();

    printf("ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!\n");


    return 0;
}