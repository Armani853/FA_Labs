#include "../include/functions.h"

const char* skip_whitespace(const char* s) {
    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r') {
        s++;
    }
    return s;

}

void log_var(Interpreter_state* state) {
    int is_first = 1;
    for (int i = 0; i < VAR_COUNT; i++) {
        if (state->is_init[i]) {
            if (!is_first) {
                fprintf(state->log_file, ", ");
            }
            fprintf(state->log_file, "%c=%d", 'A' + i, state->vars[i]);
            is_first = 0;
        }
    }
}

void log_trace(Interpreter_state* state, char* cleaned_line, char* op_desc) {
    if (!state->log_file) {
        return;
    }
    fprintf(state->log_file, "%zu %s  ", state->line_num, cleaned_line);
    log_var(state);
    fprintf(state->log_file, "   %s\n", op_desc);
    fflush(state->log_file);
}

StatusCode init_inter(Interpreter_state* state, const char* log_filename) {
    state->line_num = 0;
    for (int i = 0; i < VAR_COUNT; i++) {
        state->vars[i] = 0;
        state->is_init[i] = 0;
    }
    state->log_file = fopen(log_filename, "w");
    if (!state->log_file) {
        return OPEN_ERROR;
    }

    return STATUS_OK;

}

int power(int a, int b) {
    if (b < 0) {
        return 0;
    }
    int res = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            res *= a;
        }
        a *= a;
        b /= 2;
    }
    return res;
    
}

const char* parse_factor(Interpreter_state* state, const char* s, int* res, StatusCode* st) {
    if (*st != STATUS_OK) {
        return s;
    }
    s = skip_whitespace(s);
    int sign = 1;
    if (*s == '-') {
        sign = -1;
        s++;
        s = skip_whitespace(s);
    }
    if (isdigit(*s)) {
        *res = 0;
        while (isdigit(*s)) {
            *res = *res * 10 + (*s - '0');
            s++;
        }
        *res *= sign;
    } else if (*s >= 'A' && *s <= 'Z') {
        int var_ind = *s - 'A';
        if (!state->is_init[var_ind]) {
            *st = UNINIT_VAR;
            return s;
        }
        *res = state->vars[var_ind];
        s++;
    } else if (*s == '(') {
        s++;
        s = parse_exp(state, s, res, st);
        if (*st != STATUS_OK) {
            return s;
        }
        s = skip_whitespace(s);
        if (*s != ')') {
            *st = ERROR_SYNTAX;
            return s;
        }
        s++;
    } else {
        *st = ERROR_SYNTAX;
    }
    return s;

}

const char* parse_term(Interpreter_state* state, const char* s, int* res, StatusCode* st) {
    if (*st != STATUS_OK) {
        return s;
    }
    s = skip_whitespace(s);
    s = parse_factor(state, s, res, st);
    if (*st != STATUS_OK) {
        return s;
    }
    s = skip_whitespace(s);
    while (*s == '*' || *s == '/' || *s == '^') {
        char op = *s++;
        s = skip_whitespace(s);
        int factor_val;
        s = parse_factor(state, s, &factor_val, st);
        if (*st != STATUS_OK) {
            return s;
        }
        if (op == '*') {
            *res *= factor_val;
        } else if (op == '/') {
            if (factor_val == 0) {
                *st = DIV_BY_ZERO;
                return s;
            }
            *res /= factor_val;
        } else if (op == '^') {
            *res = power(*res, factor_val);
        }
        s = skip_whitespace(s);
    }
    return s;
}

const char* parse_exp(Interpreter_state* state, const char* s, int* res, StatusCode* st) {
    if (*st != STATUS_OK) {
        return s;
    }
    s = skip_whitespace(s);
    s = parse_term(state, s, res, st);
    if (*st != STATUS_OK) {
        return s;
    }
    s = skip_whitespace(s);
    while (*s == '+' || *s == '-') {
        char op = *s;
        s++;
        s = skip_whitespace(s);
        int term_val;
        s = parse_term(state, s, &term_val, st);
        if (*st != STATUS_OK) {
            return s;
        }
        if (op == '+') {
            *res += term_val;
        } else if (op == '-') {
            *res -= term_val;
        }
        s = skip_whitespace(s);
    }
    return s;
}

StatusCode execute_line(Interpreter_state* state, const char* line) {
    if (!state || !line) {
        return INVALID_INPUT;
    }
    state->line_num++;
    StatusCode st = STATUS_OK;
    char op_desc[64] = "Unknown operation";
    char cleaned_line[MAX_LINE_LENGTH];
    strncpy(cleaned_line, line, MAX_LINE_LENGTH);
    cleaned_line[MAX_LINE_LENGTH - 1] = '\0';
    char* newline = strchr(cleaned_line, '\n');
    if (newline) {
        *newline = '\0';
    }
    const char* s = skip_whitespace(line);
    if (*s >= 'A' && *s <= 'Z') {
        int var_ind = *s - 'A';
        s++;
        s = skip_whitespace(s);
        if (*s != '=') {
        st = ERROR_SYNTAX;
        } else {
            s++;
            int res;
            const char* end_ptr = parse_exp(state, s, &res, &st);
            const char* endl = skip_whitespace(end_ptr);
            if (st == STATUS_OK && endl[0] == '\0') {
                state->vars[var_ind] = res;
                state->is_init[var_ind] = 1;
                if (strchr(s, '+') || strchr(s, '-') || strchr(s, '*') || strchr(s, '/') || strchr(s, '^')) {
                    strcpy(op_desc, "Arithmetic operation");
                } else {
                    strcpy(op_desc, "Assignment");
                }
            } else if (st == STATUS_OK) {
                st = ERROR_SYNTAX;
            }
        }
    } else if (strncmp(s, "print", 5) == 0 && (*(s + 5) == '(' || *(s + 5) == ' ')) {
        s = skip_whitespace(s + 5);
        if (*s != '(') {
            st = ERROR_SYNTAX;
        } else {
            s++;
            s = skip_whitespace(s);
            int res;
            const char* endptr = parse_exp(state, s, &res, &st);
            const char* endl = skip_whitespace(endptr);
            if (st == STATUS_OK && endl[0] == ')') {
                printf("OUTPUT: %d\n", res);
                s = skip_whitespace(endl + 1);
                if (*s != '\0' && *s != '\n') {
                    st = ERROR_SYNTAX;
                }
                strcpy(op_desc, "Print Function");
            } else {
                st = ERROR_SYNTAX;
            }
        }
    } else {
        st = ERROR_SYNTAX;
    }

    if (st != STATUS_OK) {
        log_trace(state, cleaned_line, "Error");
        return st;
    } else {
        log_trace(state, cleaned_line, op_desc);
        return STATUS_OK;
    }

}