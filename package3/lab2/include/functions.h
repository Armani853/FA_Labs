#include "status_codes.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef VECTOR_TYPE
#error "Vector Type должен быть определён до включения файла"
#endif

typedef struct {
    VECTOR_TYPE* data;
    size_t size;
    size_t capacity;

    VECTOR_TYPE (*CopyFunc) (VECTOR_TYPE);
    void (*DeleteFunc) (VECTOR_TYPE);
} Vector;

#define INITIAL_CAPACITY 8
#define VECTOR_ERROR_VALUE ((VECTOR_TYPE){0})

StatusCode resize_vector(Vector* v, size_t new_capacity);

Vector create_vector(size_t initial_capacity, VECTOR_TYPE (*CopyFunc) (VECTOR_TYPE), void (*DeleteFunc) (VECTOR_TYPE));

StatusCode erase_vector(Vector* v);

StatusCode copy_vector(Vector* dest, const Vector* src);

Vector* copy_new_vector(const Vector* src);

StatusCode push_back_vector(Vector* v, VECTOR_TYPE value);

StatusCode delete_at_vector(Vector* v, size_t index);

VECTOR_TYPE get_at_vector(const Vector* v, size_t index);

StatusCode delete_vector(Vector* v);

int is_equal_vector(const Vector* v1, const Vector* v2);


