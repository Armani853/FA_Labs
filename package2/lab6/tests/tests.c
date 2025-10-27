#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/functions.h"

#define TEST_ID_1 501
#define TEST_ID_2 502

void test_student_logic();
void test_collection_management();
void test_search_and_report();

int main() {
    printf("--- Запуск Unit-тестов ---\n");
    test_student_logic();
    test_collection_management();
    test_search_and_report();
    printf("--- Все тесты успешно пройдены! ---\n");
    return 0;
}

void test_student_logic() {
    Student s;
    unsigned char grades_data[] = {100, 90, 80, 70, 60};

    assert(student_create(&s, TEST_ID_1, "Alice", "Smith", "G1", grades_data) == STATUS_OK);
    assert(s.id == TEST_ID_1);
    assert(strcmp(s.name, "Alice") == 0);
    assert(s.grades != NULL);

    assert(validate_name_surname("Ivan") == STATUS_OK);
    assert(validate_name_surname("Иван") != STATUS_OK);
    assert(validate_name_surname("A1ice") != STATUS_OK);

    assert(student_calculate_avg_grade(&s) == 80.0); 

    student_free(&s);
    printf("Тест: Базовая логика студента - ОК\n");
}

void test_collection_management() {
    Student_collection c;
    collection_init(&c);

    assert(c.count == 0);
    assert(c.capacity == 0);
    assert(c.array == NULL);

    assert(collection_resize(&c) == STATUS_OK);
    assert(c.capacity == INITIAL_CAPACITY);
    assert(c.array != NULL);

    size_t old_capacity = c.capacity;
    assert(collection_resize(&c) == STATUS_OK);
    assert(c.capacity == old_capacity * GROWTH_FACTOR);

    collection_free(&c);

    assert(c.count == 0);
    assert(c.capacity == 0);
    assert(c.array == NULL);
    printf("Тест: Управление коллекцией - ОК\n");
}

void test_search_and_report() {
    Student_collection c;
    collection_init(&c);
    unsigned char g1[] = {100, 100, 100, 100, 100};
    unsigned char g2[] = {50, 50, 50, 50, 50};
    
    assert(collection_resize(&c) == STATUS_OK);
    assert(collection_resize(&c) == STATUS_OK);
    
    assert(student_create(&c.array[0], TEST_ID_1, "John", "Doe", "G1", g1) == STATUS_OK);
    c.count++;
    assert(student_create(&c.array[1], TEST_ID_2, "Jane", "Smith", "G2", g2) == STATUS_OK);
    c.count++;

    double global_avg = collection_calculate_global_avg(&c);
    assert(global_avg == 75.0);

    StatusCode st = INVALID_INPUT;
    const Student* s_found = search_by_id(&c, TEST_ID_1, &st);
    assert(st == STATUS_OK);
    assert(s_found != NULL);
    assert(strcmp(s_found->surname, "Doe") == 0);
    
    st = STATUS_OK;
    s_found = search_by_id(&c, 999, &st);
    assert(st != STATUS_OK);
    assert(s_found == NULL);

    const Student** results = NULL;
    size_t result_count = 0;
    
    assert(search_by_string(&c, "Doe", Field_Surname, &results, &result_count) == STATUS_OK);
    assert(result_count == 1);
    assert(strcmp(results[0]->name, "John") == 0);
    
    if (results) free(results);

    results = NULL;
    result_count = 0;
    assert(search_by_string(&c, "Noname", Field_Name, &results, &result_count) != STATUS_OK);
    assert(result_count == 0);
    assert(results == NULL);

    sort_collection(&c, compare_by_id);
    assert(c.array[0].id == TEST_ID_1); 
    assert(c.array[1].id == TEST_ID_2);

    collection_free(&c);
    printf("Тест: Поиск, расчеты и сортировка - ОК\n");
}