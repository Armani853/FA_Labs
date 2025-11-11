#include "status_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START_CAPACITY 10
#define NOT_BALANCED 0
#define BALANCED 1

typedef struct {
    char* data;
    size_t size;
    size_t capacity;
} Stack;

StatusCode stack_create(Stack* s, size_t initial_capacity);

void stack_destroy(Stack* s);

StatusCode stack_push(Stack* s, char el);

StatusCode stack_resize(Stack* s, size_t new_capacity);

StatusCode stack_pop(Stack* s, char* res);

StatusCode stack_top(const Stack* s, char* res); 

int stack_is_empty(const Stack* s);

int check_brackets(const char* str);

int is_matching(char open_bracket, char close_bracket);