#include "status_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VAR_COUNT 26
#define MAX_LINE_LENGTH 512

typedef struct {
    int vars[VAR_COUNT];
    int is_init[VAR_COUNT];
    size_t line_num;
    FILE* log_file;
} Interpreter_state;

const char* skip_whitespace(const char* s);

void log_var(Interpreter_state* state);

void log_trace(Interpreter_state* state, char* cleaned_line, char* op_desc);

StatusCode init_inter(Interpreter_state* state, const char* log_filename);

int power(int a, int b);

const char* parse_factor(Interpreter_state* state, const char* s, int* res, StatusCode* st);

const char* parse_term(Interpreter_state* state, const char* s, int* res, StatusCode* st);

const char* parse_exp(Interpreter_state* state, const char* s, int* res, StatusCode* st);

StatusCode execute_line(Interpreter_state* state, const char* line);






