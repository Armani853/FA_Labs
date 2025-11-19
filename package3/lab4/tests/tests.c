#include "../include/functions.h"

#include <assert.h>

int create_and_check(Heap *h, size_t initial_capacity) {
    if (create_heap(initial_capacity, h) != STATUS_OK) {
        return -1;
    }
    assert(h->size == 0);
    assert(h->capacity == initial_capacity);
    if (initial_capacity > 0) {
        assert(h->data != NULL);
    }
    return 0;
}

void test_create_and_delete() {
    printf("Тест: create_heap и delete_heap\n");
    Heap h;
    assert(create_and_check(&h, 10) == 0);
    assert(is_empty_heap(&h) == 1);
    assert(size_heap(&h) == 0);
    delete_heap(&h);
    
    assert(create_and_check(&h, 0) == 0);
    delete_heap(&h);
    
    printf("Тест пройден.\n");
}

void test_push_and_peek() {
    printf("Тест: push_heap и peek_heap (Min-Heap)\n");
    Heap h;
    create_heap(4, &h);
    int res;

    push_heap(&h, 30);
    push_heap(&h, 10);
    push_heap(&h, 40);
    push_heap(&h, 5); 
    
    assert(size_heap(&h) == 4);
    assert(peek_heap(&h, &res) == STATUS_OK);
    assert(res == 5);
    
    push_heap(&h, 50); 
    assert(h.capacity == 8);
    assert(size_heap(&h) == 5);
    assert(peek_heap(&h, &res) == STATUS_OK);
    assert(res == 5);

    delete_heap(&h);
    printf("Тест пройден.\n");
}

void test_pop() {
    printf("Тест: pop_heap (Min-Heap)\n");
    Heap h;
    create_heap(4, &h);
    int res;
    int data[] = {30, 10, 40, 5, 50};
    for(int i = 0; i < 5; ++i) push_heap(&h, data[i]);
    
    assert(pop_heap(&h, &res) == STATUS_OK);
    assert(res == 5);
    assert(size_heap(&h) == 4);
    assert(h.data[0] == 10);
    
    assert(pop_heap(&h, &res) == STATUS_OK);
    assert(res == 10);
    assert(size_heap(&h) == 3);
    
    assert(pop_heap(&h, &res) == STATUS_OK);
    assert(res == 30);
    assert(size_heap(&h) == 2);
    
    delete_heap(&h);
    printf("Тест пройден.\n");
}

void test_build_heap() {
    printf("Тест: build_heap\n");
    Heap h1;
    create_heap(0, &h1);
    int array[] = {10, 50, 20, 80, 15};
    size_t n = 5;

    assert(build_heap(&h1, array, n) == STATUS_OK);
    assert(h1.size == n);
    
    int expected[] = {10, 15, 20, 80, 50};
    assert(memcmp(h1.data, expected, n * sizeof(int)) == 0);
    
    delete_heap(&h1);
    printf("Тест пройден.\n");
}

void test_compare_heap() {
    printf("Тест: compare_heap\n");
    Heap h2, h3;
    create_heap(0, &h2);
    create_heap(0, &h3);
    int array[] = {10, 50, 20, 80, 15};
    size_t n = 5;
    int res;

    build_heap(&h2, array, n);
    build_heap(&h3, array, n);
    assert(compare_heap(&h2, &h3) == STATUS_OK);

    pop_heap(&h3, &res);
    push_heap(&h3, 100);
    assert(compare_heap(&h2, &h3) == NOT_EQUAL_ERROR);

    pop_heap(&h3, &res);
    assert(compare_heap(&h2, &h3) == NOT_EQUAL_ERROR);
    
    delete_heap(&h2);
    delete_heap(&h3);
    printf("Тест пройден.\n");
}

void test_edge_cases() {
    printf("Тест: граничные случаи\n");
    Heap h;
    create_heap(1, &h);
    int res;

    assert(is_empty_heap(&h) == 1);
    assert(peek_heap(&h, &res) != STATUS_OK);
    assert(pop_heap(&h, &res) != STATUS_OK);
    
    push_heap(&h, 42);
    assert(size_heap(&h) == 1);
    assert(peek_heap(&h, &res) == STATUS_OK);
    assert(res == 42);
    
    assert(pop_heap(&h, &res) == STATUS_OK);
    assert(res == 42);
    assert(is_empty_heap(&h) == 1);

    delete_heap(&h);
    printf("Тест пройден.\n");
}

int main() {
    printf("--- АВТОМАТИЧЕСКОЕ ТЕСТИРОВАНИЕ HEAP (assert) ---\n");
    test_create_and_delete();
    test_push_and_peek();
    test_pop();
    test_build_heap();
    test_compare_heap();
    test_edge_cases();
    printf("--- ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО. ---\n");
    return EXIT_SUCCESS;
}