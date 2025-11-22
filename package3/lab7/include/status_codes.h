#ifndef STATUS_CODES_H
#define STATUS_CODES_H

typedef enum {
    STATUS_OK = 0,
    INVALID_INPUT = 1,
    MEMORY_ERROR = 2,
    OPEN_ERROR = 3,
    ERROR_SYNTAX = 4,
    DIV_BY_ZERO = 5,
    UNINIT_VAR = 6
} StatusCode;

#endif