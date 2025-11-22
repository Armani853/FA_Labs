#include <assert.h>

#include "../include/functions.h"

void test_power() {
    assert(power(2, 3) == 8);
    assert(power(10, 0) == 1);
    assert(power(1, 5) == 1);
    assert(power(-2, 3) == -8);
    assert(power(5, 1) == 5);

    printf("Power tests passed.\n");
}

void test_execute_line() {
    Interpreter_state state = {0};
    const char *log_file_name = "test_trace.log";
    StatusCode s;

    s = init_inter(&state, log_file_name);
    assert(s == STATUS_OK);

    s = execute_line(&state, "A = 10\n");
    assert(s == STATUS_OK);
    assert(state.vars['A' - 'A'] == 10);
    assert(state.is_init['A' - 'A'] == 1);

    s = execute_line(&state, "B = A + 5 * 2\n");
    assert(s == STATUS_OK);
    assert(state.vars['B' - 'A'] == 20);

    s = execute_line(&state, "C = B ^ 2\n");
    assert(s == STATUS_OK);
    assert(state.vars['C' - 'A'] == 400);

    s = execute_line(&state, "D = (C - 40) / 36\n");
    assert(s == STATUS_OK);
    assert(state.vars['D' - 'A'] == 10);
    
    s = execute_line(&state, "E = D / (D - 10)\n");
    assert(s == DIV_BY_ZERO);
    
    s = execute_line(&state, "F = G + 1\n");
    assert(s == UNINIT_VAR);

    s = execute_line(&state, "H = (A + B\n");
    assert(s == ERROR_SYNTAX);

    s = execute_line(&state, "I = 10 * 5 лишний текст\n");
    assert(s == ERROR_SYNTAX);

    s = execute_line(&state, "print(2 * 5)\n");
    assert(s == STATUS_OK);
    
    if (state.log_file) {
        fclose(state.log_file);
        state.log_file = NULL;
    }
    printf("Execute_line tests passed.\n");
}

int main() {
    printf("--- Running Unit Tests ---\n");
    test_power();
    test_execute_line();
    printf("\nAll tests successfully completed!\n");
    return 0;
}