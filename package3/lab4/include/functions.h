#include "status_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} Heap;

StatusCode create_heap(size_t initial_capacity, Heap* h);

void delete_heap(Heap* h);

int is_empty_heap(const Heap* h);

size_t size_heap(const Heap* h);

StatusCode peek_heap(Heap* h, int* res);

StatusCode push_heap(Heap* h, int value);

StatusCode pop_heap(Heap* h, int* res);

StatusCode build_heap(Heap* h, const int* arr, size_t n);

StatusCode compare_heap(Heap* h1, Heap* h2);

StatusCode heap_resize(Heap *h, size_t new_capacity);

void heapify_down(Heap *h, size_t index);

void heapify_up(Heap *h, size_t index);


