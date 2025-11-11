#define VECTOR_TYPE char*
#include "../include/functions.h"


StatusCode resize_vector(Vector* v, size_t new_capacity) {
    if (new_capacity < v->size) {
        new_capacity = v->size;
        return STATUS_OK;
    }
    VECTOR_TYPE* new_data = (VECTOR_TYPE* )realloc(v->data, new_capacity * sizeof(VECTOR_TYPE));
    if (new_data == NULL) {
        return MEMORY_ERROR;
    }
    v->data = new_data;
    v->capacity = new_capacity;
    return STATUS_OK;
}

Vector create_vector(size_t initial_capacity, VECTOR_TYPE (*CopyFunc) (VECTOR_TYPE), void (*DeleteFunc) (VECTOR_TYPE)) {
    Vector v;
    if (initial_capacity == 0) {
       initial_capacity = INITIAL_CAPACITY;
    }
    v.data = (VECTOR_TYPE * )malloc(initial_capacity * sizeof(VECTOR_TYPE));
    if (v.data == NULL) {
        v.capacity = 0;
    } else {
        v.capacity = initial_capacity;
    }

    v.size = 0;
    v.CopyFunc = CopyFunc;
    v.DeleteFunc = DeleteFunc;

    return v;

}

StatusCode erase_vector(Vector* v) {
    if (v == NULL) {
        return INVALID_INPUT;
    }
    if (v->DeleteFunc != NULL) {
        for (size_t i = 0; i < v->size; i++) {
            v->DeleteFunc(v->data[i]);
        }
    }
    if (v->data != NULL) {
        free(v->data);
    }

    v->size = 0;
    v->capacity = 0;
    v->data = NULL;
    return STATUS_OK;
}

int is_equal_vector(const Vector* v1, const Vector* v2) {
    if (v1 == NULL || v2 == NULL || v1->size != v2->size) {
        return 0;
    }

    if (v1 == v2) {
        return 1;
    }

    for (size_t i = 0; i < v1->size; i++) {
        if (strcmp(v1->data[i], v2->data[i]) != 0) {
            return 0;
        }
    }
    return 1;
}


StatusCode copy_vector(Vector* dest, const Vector* src) {
    if (dest == NULL || src == NULL) {
        return INVALID_INPUT;
    }
    if (src == dest) {
        return STATUS_OK;
    }
    StatusCode er = erase_vector(dest);
    if (er != STATUS_OK) {
        return er;
    }

    dest->CopyFunc = src->CopyFunc;
    dest->DeleteFunc = src->DeleteFunc;

    if (dest->capacity < src->size) {
        if (resize_vector(dest, src->size) != STATUS_OK) {
            return MEMORY_ERROR;
        };
    }

    if (dest->data == NULL) {
        return MEMORY_ERROR;
    }
    if (src->CopyFunc != NULL) {
        for (size_t i = 0; i < src->size; i++) {
            dest->data[i] = src->CopyFunc(src->data[i]);
        }
    } else {
        for (size_t i = 0; i < src->size; i++) {
            dest->data[i] = src->data[i];
        }
    }
    dest->size = src->size;
    return STATUS_OK;
}

Vector* copy_new_vector(const Vector* src) {
    if (src == NULL) {
        return NULL;
    }
    Vector* new_v = (Vector*)malloc(sizeof(Vector));
    if (new_v == NULL) {
        return NULL;
    }
    new_v->size = 0;
    new_v->capacity = 0;
    new_v->data = NULL;

    if (copy_vector(new_v, src) != STATUS_OK) {
        free(new_v);
        return NULL;
    };

    return new_v;
}

StatusCode push_back_vector(Vector* v, VECTOR_TYPE value) {
    if (v == NULL) {
        return MEMORY_ERROR;
    }
    if (v->size >= v->capacity) {
        size_t new_capacity;
        if (v->capacity > 0) {
            new_capacity = 2 * v->capacity;
        } else {
            new_capacity = INITIAL_CAPACITY;
        } 
        if (resize_vector(v, new_capacity) != STATUS_OK) {
            return MEMORY_ERROR;
        };
    }

    if (v->CopyFunc != NULL) {
        v->data[v->size] = v->CopyFunc(value);
    } else {
        v->data[v->size] = value;
    }
    v->size++;
    return STATUS_OK;
}

StatusCode delete_at_vector(Vector* v, size_t index) {
    if (v == NULL || index >= v->size) {
        return INVALID_INPUT;
    }
    if (v->DeleteFunc != NULL) {
        v->DeleteFunc(v->data[index]);
    }
    for (size_t i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }
    v->size--;
    return STATUS_OK;
}

VECTOR_TYPE get_at_vector(const Vector* v, size_t index) {
    if (v == NULL || index >= v->size) {
        return VECTOR_ERROR_VALUE;
    }
    return v->data[index];
}

StatusCode delete_vector(Vector* v) {
    return erase_vector(v);
}




