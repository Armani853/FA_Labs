#include "../include/functions.h"

void heapify_up(Heap *h, size_t index) {
    if (index == 0) return;
    
    size_t parent_index = (index - 1) / 2;

    if (h->data[index] < h->data[parent_index]) {
        int temp = h->data[index];
        h->data[index] = h->data[parent_index];
        h->data[parent_index] = temp;
        
        heapify_up(h, parent_index);
    }
}

void heapify_down(Heap *h, size_t index) {
    size_t left_child = 2 * index + 1;
    size_t right_child = 2 * index + 2;
    size_t smallest = index;

    if (left_child < h->size && h->data[left_child] < h->data[smallest]) {
        smallest = left_child;
    }
    if (right_child < h->size && h->data[right_child] < h->data[smallest]) {
        smallest = right_child;
    }

    if (smallest != index) {
        int temp = h->data[index];
        h->data[index] = h->data[smallest];
        h->data[smallest] = temp;
        
        heapify_down(h, smallest);
    }
}

StatusCode heap_resize(Heap *h, size_t new_capacity) {
    if (new_capacity < h->size) {
        return INVALID_INPUT;
    }

    if (new_capacity == h->capacity) return STATUS_OK;
    
    int *new_data = (int*)realloc(h->data, new_capacity * sizeof(int));

    if (new_data == NULL) {
        return MEMORY_ERROR;
    }

    h->data = new_data;
    h->capacity = new_capacity;
    return STATUS_OK;
}



StatusCode create_heap(size_t initial_capacity, Heap* h) {
    if (h == NULL) {
        return INVALID_INPUT;
    }
    h->size = 0;
    h->capacity = 0;
    h->data = NULL;

    if (initial_capacity > 0) {
        h->data = (int*)malloc(sizeof(int) * initial_capacity);
        if (h->data == NULL) {
            return MEMORY_ERROR;
        }
        h->capacity = initial_capacity;
    }
    return STATUS_OK;
}


void delete_heap(Heap* h) {
    if (h == NULL) {
        return;
    }
    if (h->data != NULL) {
        free(h->data);
    }
    h->data = NULL;
    h->size = 0;
    h->capacity = 0;
}

int is_empty_heap(const Heap* h) {
    if (h == NULL) {
        return 1;
    }
    return (h->size == 0);
}

size_t size_heap(const Heap* h) {
    if (h == NULL) {
        return 0;
    }
    return (h->size);
}

StatusCode peek_heap(Heap* h, int* res) {
    if (h == NULL || res == NULL || is_empty_heap(h)) {
        return INVALID_INPUT;
    }
    *res = h->data[0];
    return STATUS_OK;
}

StatusCode push_heap(Heap* h, int value) {
    if (h == NULL) {
        return INVALID_INPUT;
    }
    if (h->size == h->capacity) {
        size_t new_capacity = h->capacity * 2;
        StatusCode s = heap_resize(h, new_capacity);
        if (s != STATUS_OK) {
            return s;
        }
     }
     h->data[h->size] = value;
     h->size++;

     heapify_up(h, h->size - 1);
     return STATUS_OK;
 }

StatusCode pop_heap(Heap* h, int* res) {
    if (h == NULL || res == NULL || is_empty_heap(h)) {
        return INVALID_INPUT;
    }
    *res = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;

    if (h->size > 0) {
        heapify_down(h, 0);
    }
    return STATUS_OK;
}

StatusCode build_heap(Heap* h, const int* arr, size_t n) {
    if (h == NULL || arr == NULL || n == 0) {
        return INVALID_INPUT;
    }

    if (h->capacity < n) {
        StatusCode s = heap_resize(h, n);
        if (s != STATUS_OK) {
            return s;
        }
    }
    memcpy(h->data, arr, n * sizeof(int));
    h->size = n;

    if (n > 0) {
        for (size_t i = n / 2; i > 0; --i) {
            heapify_down(h, i - 1);
        }
    }

    return STATUS_OK;
}

StatusCode compare_heap(Heap* h1, Heap* h2) {
    if (h1 == NULL || h2 == NULL) {
        return INVALID_INPUT;
    }
    if (h1->size != h2->size) {
        return NOT_EQUAL_ERROR;
    }

    if (memcmp(h1->data, h2->data, h1->size * sizeof(int)) != 0) {
        return NOT_EQUAL_ERROR;
    }

    return STATUS_OK;
}












