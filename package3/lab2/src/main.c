#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_TYPE char*

#include "../include/functions.h"

VECTOR_TYPE str_copy_func(VECTOR_TYPE src) {
    if (src == NULL) {
        return NULL;
    }
    return strdup(src);
}

void str_delete_func(VECTOR_TYPE src) {
    if (src != NULL) {
        free(src);
    }
}

int main() {
    printf("Тестирование динамического массива: \n\n");

    Vector vec = create_vector(2, str_copy_func, str_delete_func);
    printf("1. Создан вектор. Размер: %zu, Вместимость: %zu\n", vec.size, vec.capacity);

    printf("2. Добавляем элементы: \n");
    push_back_vector(&vec, "Hello");
    push_back_vector(&vec, "World");
    push_back_vector(&vec, "That is me, Armani");

    printf("Текущий размер: %zu, Вместимость: %zu\n", vec.size, vec.capacity);

    printf("   Элемент [1]: %s\n", get_at_vector(&vec, 1));
    printf("   Элемент [0]: %s\n", get_at_vector(&vec, 0));
    
    Vector *vec_copy = copy_new_vector(&vec);
    printf("3. Создана глубокая копия. Размер: %zu, Элемент [2]: %s\n", vec_copy->size, get_at_vector(vec_copy, 2));

    printf("4. Сравнение (vec == vec_copy): %s\n", is_equal_vector(&vec, vec_copy) ? "Равны (1)" : "Не равны (0)");
    
    printf("5. Удаляем элемент [0] ('Hello').\n");
    delete_at_vector(&vec, 0);
    printf("   Текущий размер: %zu, Новый элемент [0]: %s\n", vec.size, get_at_vector(&vec, 0));
    
    printf("6. Очищаем (erase) vec_copy.\n");
    erase_vector(vec_copy);
    printf("   vec_copy Размер: %zu, Вместимость: %zu\n", vec_copy->size, vec_copy->capacity);
    
    delete_vector(&vec);
    free(vec_copy);

    printf("7. Память освобождена.\n");
    return 0;
}