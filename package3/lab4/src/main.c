#include "../include/functions.h"


void print_heap(const Heap *h, const char *name) {
    if (h == NULL) {
        printf("Куча %s: NULL\n", name);
        return;
    }
    printf("Куча %s (size=%zu, capacity=%zu): [", name, h->size, h->capacity);
    for (size_t i = 0; i < h->size; ++i) {
        printf("%d", h->data[i]);
        if (i < h->size - 1) printf(", ");
    }
    printf("]\n");
}

void run_heap_tests() {
    printf("ТЕСТИРОВАНИЕ БИБЛИОТЕКИ HEAP (Min-Heap)\n");
    
    Heap h1; 
    StatusCode s_create = create_heap(4, &h1);
    if (s_create != STATUS_OK) {
        printf("Ошибка при создании h1. Статус: %d\n", s_create);
        return;
    }
    
    int res;
    StatusCode s;
    int array[] = {10, 50, 20, 80, 15};

    printf("\n1. PUSH-операции:\n");
    push_heap(&h1, 30);
    push_heap(&h1, 10);
    push_heap(&h1, 40);
    push_heap(&h1, 5);
    push_heap(&h1, 50); 
    print_heap(&h1, "h1");
    
    s = peek_heap(&h1, &res);
    printf("   Peek (ожидается 5): %d. Статус: %d\n", res, s);

    printf("\n2. POP-операции:\n");
    s = pop_heap(&h1, &res);
    printf("   Pop (ожидается 5): %d. Статус: %d\n", res, s);
    s = pop_heap(&h1, &res);
    printf("   Pop (ожидается 10): %d. Статус: %d\n", res, s);
    print_heap(&h1, "h1 после 2 pop");
    
    printf("\n3. BUILD_HEAP:\n");
    Heap h2;
    create_heap(0, &h2); 
    s = build_heap(&h2, array, 5);
    printf("   Build статус: %d\n", s);
    print_heap(&h2, "h2");

    printf("\n4. COMPARE_HEAP:\n");
    Heap h3;
    create_heap(0, &h3);
    
    build_heap(&h3, array, 5);
    s = compare_heap(&h2, &h3);
    printf("   h2 и h3 (идентичные): %d (Ожидается STATUS_OK)\n", s);
    
    pop_heap(&h3, &res);
    push_heap(&h3, 100);
    print_heap(&h3, "h3 модифицированная");
    
    s = compare_heap(&h2, &h3);
    printf("   h2 и h3 (разные): %d (Ожидается NOT_EQUAL_ERROR)\n", s);
    
    delete_heap(&h1);
    delete_heap(&h2);
    delete_heap(&h3);
    printf("\nПамять куч освобождена.\n");
}

int main() {
    run_heap_tests();
    return EXIT_SUCCESS;
}