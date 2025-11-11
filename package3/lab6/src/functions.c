#include "../include/functions.h"


StatusCode stack_resize(Stack* s, size_t new_capacity) {
    if (s == NULL || new_capacity <= s->capacity) {
        return INVALID_INPUT;
    }
    char* new_data = (char* )realloc(s->data, new_capacity * sizeof(char));
    if (new_data == NULL) {
        return MEMORY_ERROR;
    }
    s->data = new_data;
    s->capacity = new_capacity;
    return STATUS_OK;

}


StatusCode stack_create(Stack* s, size_t initial_capacity) {
    if (s == NULL || initial_capacity <= 0) {
        return INVALID_INPUT;
    }

    s->size = 0;
    s->capacity = initial_capacity;
    s->data = NULL;

    s->data = (char *)malloc(initial_capacity * sizeof(char));
    if (s->data == NULL) {
        s->capacity = 0;
        return MEMORY_ERROR;
    }
    return STATUS_OK;
}

void stack_destroy(Stack* s) {
    if (s == NULL) {
        return;
    }
    if (s->data != NULL) {
        free(s->data);
    }
    s->capacity = 0;
    s->size = 0;
    s->data = NULL;
}

StatusCode stack_push(Stack* s, char el) {
    if (s == NULL) {
        return INVALID_INPUT;
    }
    if (s->capacity == s->size) {
        size_t new_capacity;
        if (s->capacity == 0) {
            new_capacity = START_CAPACITY;
        } else {
            new_capacity = s->capacity * 2;
        }
        StatusCode st = stack_resize(s, new_capacity);
        if (st != STATUS_OK) {
            return st;
        }
    }
    s->data[s->size] = el;
    s->size++;
    return STATUS_OK;
}

StatusCode stack_pop(Stack* s, char* res) {
    if (s == NULL || res == NULL || s->size == 0) {
        return INVALID_INPUT;
    }
    *res = s->data[s->size - 1];
    s->size--;
    return STATUS_OK;
}

StatusCode stack_top(const Stack* s, char* res) {
    if (s == NULL || res == NULL || s->size == 0) {
        return INVALID_INPUT;
    }
    *res = s->data[s->size - 1];
    return STATUS_OK;
}

int stack_is_empty(const Stack* s) {
    if (s == NULL) {
        return 0;
    }
    return (s->size == 0);
}


int is_matching(char open_bracket, char close_bracket) {
    if (open_bracket == '(' && close_bracket == ')') {
        return 1;
    }
    if (open_bracket == '<' && close_bracket == '>') {
        return 1;
    }
    if (open_bracket == '{' && close_bracket == '}') {
        return 1;
    }
    if (open_bracket == '[' && close_bracket == ']') {
        return 1;
    }
    return 0;
}

int check_brackets(const char* str) {
    if (str == NULL) {
        return NOT_BALANCED;
    }
    Stack stack_ex;
    StatusCode st = stack_create(&stack_ex, START_CAPACITY);
    if (st != STATUS_OK) {
        return NOT_BALANCED;
    }
    int res = NOT_BALANCED;
    for (size_t i = 0; i < strlen(str); i++) {
        char curr_ch = str[i];
        char top_brack;
        switch(curr_ch) {
            case '(':
            case '[':
            case '{':
            case '<':
                StatusCode push_st = stack_push(&stack_ex, curr_ch);
                if (push_st != STATUS_OK) {
                    stack_destroy(&stack_ex);
                    return NOT_BALANCED;
                }
                break;
            case ')':
            case '>':
            case ']':
            case '}':
                StatusCode pop_st = stack_pop(&stack_ex, &top_brack);  
                if (pop_st != STATUS_OK) {
                    stack_destroy(&stack_ex);
                    return NOT_BALANCED;
                }
                if (!is_matching(top_brack, curr_ch)) {
                    return NOT_BALANCED;
                }        
                break;
            default:
                break;
        }
    }
    if (stack_is_empty(&stack_ex) == 0) {
        res = NOT_BALANCED;
    } else {
        res = BALANCED;
    }
    stack_destroy(&stack_ex);
    return res;
}


