#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <errno.h>
int main(int argc, char* argv[]) {
    if (argc != 3) {
        return INVALID_INPUT;
    }
    char* flag = argv[1];
    if (flag[0] != '-' && flag[0] != '/') {
        return INVALID_INPUT;
    }
    char* endptr;
    int num = strtol(argv[2], &endptr, 10);
    if (*endptr != 0 || endptr == argv[2]) {
        return INVALID_INPUT;
    }
    StatusCode status;
    switch (flag[1]) {
        case 'h':
            status = dividers(num);
            break;
        case 'p':
            status = is_prime(num);
            break;
        case 's':
            status = divide_hex(num);
            break;
        case 'e':
            status = degrees(num);
            break;
        case 'a':
            status = sum(num);
            break;
        case 'f':
            status = fac(num);
            break;
        default:
            return INVALID_INPUT;
    }
    return 0;
}